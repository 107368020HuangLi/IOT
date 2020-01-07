package com.example.mycomputer.iot_fa;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ProgressBar;

public class video extends AppCompatActivity {

    WebView  wv2;
    ProgressBar pb2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video);

        wv2= (WebView) findViewById(R.id.wv2);
        pb2 = (ProgressBar)findViewById(R.id.pb2);
        SharedPreferences.Editor editor = getPreferences(MODE_PRIVATE).edit();

        // WebSettings webSettings = webView.getSettings();
        // webSettings.setJavaScriptEnabled(true);

        wv2.getSettings().setJavaScriptEnabled(true);       ///////
        wv2.getSettings().setBuiltInZoomControls(true);   //////////
        wv2.invokeZoomPicker();                            ///////

        wv2.setWebViewClient(new WebViewClient());
        wv2.loadUrl("http://192.168.43.61:8080/browserfs.html");
    }

    public void onBackPressed(){
        if(wv2.canGoBack()){
            wv2.goBack();
        }else {
            super.onBackPressed();
        }
    }

    public void go_back(View V){
        finish();
    }
}
