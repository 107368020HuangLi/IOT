package com.example.mycomputer.rtsp;

import android.content.SharedPreferences;
import android.os.Process;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ProgressBar;

public class MainActivity extends AppCompatActivity {

    WebView  wv;
    ProgressBar pb;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        wv= (WebView) findViewById(R.id.wv);
        pb = (ProgressBar)findViewById(R.id.pb);
        SharedPreferences.Editor editor = getPreferences(MODE_PRIVATE).edit();

       // WebSettings webSettings = webView.getSettings();
       // webSettings.setJavaScriptEnabled(true);
        
        wv.getSettings().setJavaScriptEnabled(true);       ///////
        wv.getSettings().setBuiltInZoomControls(true);   //////////
        wv.invokeZoomPicker();                            ///////

        wv.setWebViewClient(new WebViewClient());
        wv.loadUrl("http://192.168.0.119:8080/browserfs.html");
    }


    public void onBackPressed(){
        if(wv.canGoBack()){
            wv.goBack();
        }else {
            super.onBackPressed();
        }
    }

}
