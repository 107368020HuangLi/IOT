package com.example.mycomputer.iot_fa;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void goto_See_data(View V){
        Intent it = new Intent(this,Data_server.class);
        startActivity(it);
    }

    public void goto_See_video(View V){
        Intent it = new Intent(this,video.class);
        startActivity(it);
    }
}
