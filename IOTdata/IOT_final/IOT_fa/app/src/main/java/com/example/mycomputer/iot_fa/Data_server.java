package com.example.mycomputer.iot_fa;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ProgressBar;

public class Data_server extends AppCompatActivity {

    WebView wv;
    ProgressBar pb;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_data_server);

        wv= (WebView) findViewById(R.id.wv);
        pb = (ProgressBar)findViewById(R.id.pb);
        SharedPreferences.Editor editor = getPreferences(MODE_PRIVATE).edit();

        // WebSettings webSettings = webView.getSettings();
        // webSettings.setJavaScriptEnabled(true);

        wv.getSettings().setJavaScriptEnabled(true);       ///////
        wv.getSettings().setBuiltInZoomControls(true);   //////////
        wv.invokeZoomPicker();                            ///////

        wv.setWebViewClient(new WebViewClient());
        wv.loadUrl("http://140.124.72.10/IOT/show.php");
    }

    public void go_back(View V){
        finish();
    }
}
