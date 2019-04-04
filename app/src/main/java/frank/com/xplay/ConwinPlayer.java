package frank.com.xplay;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.SurfaceView;

import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.SocketTimeoutException;
import java.net.URL;
import java.nio.BufferOverflowException;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by zhongchao on 2019/3/29.
 */
public class ConwinPlayer extends AppCompatActivity {
    private SurfaceView mSurfaceView;
    private String mUrl;
    private BufferQueue<byte[]> mBufferQueue;
    private ByteBuffer mStreamBuffer;
    private int mSplitLen = 0;
    private int mCompareIndex = 0;
    private byte[] mSplitBytes;
    private int[] mSplitNext;
    private boolean mIsParserHeader = false;
    private boolean mStopReceive = false;
    private boolean mStopParser = false;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_conwin_player);
        mSurfaceView = findViewById(R.id.surface_view);
        mUrl = getIntent().getStringExtra("url");
        mUrl = "http://192.168.3.216:7000/stream/3d7rqaX18rkFh4x1HEoNobR6?token=test";
        initSplit();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (null != mStreamBuffer) {
            mStreamBuffer.clear();
            mStreamBuffer = null;
        }

        if (null != mBufferQueue) {
            mBufferQueue.clear();
            mBufferQueue = null;
        }
    }

    private void initSplit() {
        String split = "\r\n\r\n";
        mSplitBytes = split.getBytes();
        mSplitLen = mSplitBytes.length;
        mSplitNext = new int[mSplitLen];
        transformKMPNext(mSplitNext, mSplitBytes);
        requestStream();
    }

    private void transformKMPNext(int[] next, byte[] str) {
        next[0] = -1;
        int k = -1;
        int j = 0;
        while (j < str.length - 1) {
            if (k == -1 || str[j] == str[k]) {
                j++;
                k++;
                next[j] = k;
            } else {
                k = next[k];
            }
        }
    }

    private void requestStream() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    URL url = new URL(mUrl);
                    HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                    conn.setConnectTimeout(14*1000);
                    conn.setReadTimeout(10*1000);
                    conn.setRequestProperty("Connection", "Keep-Alive");
                    conn.setRequestProperty("User-Agent", "CONWIN");
                    conn.setRequestMethod("GET");
                    conn.connect();

                    InputStream inputStream = conn.getInputStream();

                    if (HttpURLConnection.HTTP_OK == conn.getResponseCode()) {
                        //start receive real stream data
                        readyToReceiveStream(inputStream);
                    } else {
                    }

                    mStopReceive = true;
                    inputStream.close();
                    conn.disconnect();
                } catch (ProtocolException | SocketTimeoutException e) {
                    e.printStackTrace();
                    mStopReceive = true;
                } catch (IOException e) {
                    e.printStackTrace();
                    mStopReceive = true;
                }
            }
        }).start();
    }

    private void readyToReceiveStream(InputStream inputStream) {
        //reinitialize queue buffer
        resetBufferQueue();

        //schedule parser stream data
        scheduleParserStream();

        //receive data from stream
        receiveStream(inputStream);
    }

    private void resetBufferQueue() {
        mStopReceive = false;
        mStopParser = false;

        if (null != mStreamBuffer) {
            mStreamBuffer.clear();
            mStreamBuffer = null;
        }

        if (null != mBufferQueue) {
            mBufferQueue.clear();
            mBufferQueue = null;
        }

        //buffer is cache for image, The image size is about <80K
        mStreamBuffer = ByteBuffer.allocate(1024 * 250 * 2);
        mBufferQueue = new BufferQueue<>();
    }

    private void scheduleParserStream() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (!mStopParser) {
                    //当实时流数据已经停止接收，并且队列为空，说明接收中的队列已经没有数据了，此时应当停止解析
                    if (mStopReceive && null != mBufferQueue && mBufferQueue.isEmpty()) {
                        mStopParser = true;
                        return;
                    }
                    parserStream();
                }
            }
        }).start();
    }

    private void receiveStream(InputStream inputStream) {
        while (!mStopReceive) {
            int len = -1;
            try {
                //The data of length by next read, end by -1.
                len = inputStream.available();

            } catch (IOException e) {
                e.printStackTrace();
            }

            if (len != -1) {
                byte[] read = new byte[len];
                try {
                    int readLen = inputStream.read(read);
//                    Log.d(TAG, "读取长度： " + readLen);
//                    Log.d(TAG, "" + new String(read));

                    if (0 < readLen) {
                        mBufferQueue.add(read);
                    }

                    if (-1 == readLen) {
                        mStopReceive = true;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    mStopReceive = true;
                }
            } else {
                //return -1 is over receive data
                mStopReceive = true;
            }
        }
    }

    private void parserStream() {
        if (null == mStreamBuffer || null == mBufferQueue) {
            return;
        }
        byte[] read = mBufferQueue.pop();

        if (null != read && 0 != read.length) {
            //写入数据缓冲区
            try {
                mStreamBuffer.put(read);
            } catch (BufferOverflowException e) {
                e.printStackTrace();
                mStopReceive = true;
                mStopParser = true;
            }

            interceptParserFileHeader();
        }
    }

    private void interceptParserFileHeader() {
        if (mIsParserHeader) {
            return;
        }

        if (null != mStreamBuffer && mStreamBuffer.position() > mSplitLen) { // buffer的长度必须大于分隔符才有比较的意义
            //记录当前填充数据后的Buffer读写的位置
            int position = mStreamBuffer.position();

            //找到文件头数据的分隔符的起始下标
            int findIndex = -1;

            int j = mCompareIndex; //主串的开始查找位置，取决于上一次的结果

            int s = 0; //匹配串初始位置
            //KMP查找分隔符，分离块数据
            while (j < position) {
                if (s == -1 || mStreamBuffer.get(j) == mSplitBytes[s]) {  //比较字符是否相等
                    j++;
                    s++;
                    if (s >= mSplitLen) {
                        //模式串被完全匹配
                        findIndex = j - mSplitLen;
                        break;
                    }
                } else {
                    s = mSplitNext[s];  //不等，主串j不变，模式串s变
                }
            }

            if (findIndex != -1) {
                //取出文件头数据
                mIsParserHeader = true;

                byte[] header = new byte[findIndex];
                mStreamBuffer.position(0);
                mStreamBuffer.mark();
                mStreamBuffer.get(header, 0, header.length);

                try {
                    String str = new String(header, "utf-8");
                    parserFileHeader(str);
                } catch (UnsupportedEncodingException e) {
                    e.printStackTrace();
                }

                //重置
                mCompareIndex = 0;

                resetBuffer(mStreamBuffer, position, findIndex, mSplitLen);
            } else {
                //若是没有找到，则将比较的下标重置到当前buffer长度 - 分隔符长度
                mCompareIndex = position - mSplitLen - 1;
            }
        }
    }

    private void resetBuffer(ByteBuffer buffer, int curPosition, int findIndex, int regexLength) {
        byte[] others = new byte[curPosition - findIndex - regexLength];

        buffer.position(findIndex + regexLength);
        buffer.mark();
        buffer.get(others, 0, curPosition - findIndex - regexLength);

        buffer.clear();
        buffer.put(others);
    }

    private void parserFileHeader(String str) {
        System.out.println("header string:"+str);
        if(TextUtils.isEmpty(str)) {
            return;
        }
        Log.d("---------------", str);
        String header[] = str.split("\r\n");

        for (String s : header) {
            if(s.startsWith("track")) {
                parserTrack(s);
            } else if(s.startsWith("boundary")) {
                parserBoundary(s);
            } else if(s.startsWith("ts")) {
                parserTs(s);
            }
        }
    }

    private void parserTrack(String s) {

    }

    private void parserBoundary(String s) {

    }

    private void parserTs(String s) {

    }


}
