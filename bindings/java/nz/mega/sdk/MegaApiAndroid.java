package nz.mega.sdk;

import android.os.Handler;
import android.os.Looper;

public class MegaApiAndroid extends MegaApiJava {
    static Handler handler = new Handler(Looper.getMainLooper());

    public MegaApiAndroid(String appKey, String userAgent, String path) {
        super(appKey, userAgent, path, new AndroidGfxProcessor());
    }

    public MegaApiAndroid(String appKey, String userAgent, String path, int clientType) {
        super(appKey, userAgent, path, new AndroidGfxProcessor(), clientType);
    }

    @Override
    void runCallback(Runnable runnable) {
        handler.post(runnable);
    }
}
