package com.example.mycomputer.mysql;

import org.json.JSONArray;
import org.json.JSONObject;

import android.app.Activity;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class MainActivity extends Activity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViews();
        setListeners();

        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
                .detectDiskReads()
                .detectDiskWrites()
                .detectNetwork()
                .penaltyLog()
                .build());


        StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder()
                .detectLeakedClosableObjects()
                .penaltyLog()
                .penaltyDeath()
                .build());

    }

        private Button button_get_record;
        private  TextView tv1;
        private void findViews() {
            button_get_record = (Button)findViewById(R.id.get_record);
             tv1 = (TextView)findViewById(R.id.tv3);
        }

        private void setListeners() {
            button_get_record.setOnClickListener(getDBRecord);
        }

        private Button.OnClickListener getDBRecord = new Button.OnClickListener() {
            public void onClick(View v) {
                // TODO Auto-generated method stub
                TableLayout user_list = (TableLayout)findViewById(R.id.user_list);
                user_list.setStretchAllColumns(true);
                TableLayout.LayoutParams row_layout = new TableLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
                TableRow.LayoutParams view_layout = new TableRow.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
                try {
                    String result = DBstring.DB1("SELECT  *  FROM ntut601");

                /*
                    SQL 結果有多筆資料時使用JSONArray
                    只有一筆資料時直接建立JSONObject物件
                    JSONObject jsonData = new JSONObject(result);
                */
                    JSONArray jsonArray = new JSONArray(result);
                    for(int i = jsonArray.length()-10; i < jsonArray.length(); i++) {
                        JSONObject jsonData = jsonArray.getJSONObject(i);
                        TableRow tr = new TableRow(MainActivity.this);
                        tr.setLayoutParams(row_layout);
                        tr.setGravity(Gravity.CENTER_HORIZONTAL);

                        TextView user_acc = new TextView(MainActivity.this);
                        user_acc.setText(jsonData.getString("id"));
                        user_acc.setLayoutParams(view_layout);

                        TextView user_pwd = new TextView(MainActivity.this);
                        user_pwd.setText(jsonData.getString("second"));
                        user_pwd.setLayoutParams(view_layout);

                        tv1.setText(jsonData.getString("second"));

                        tr.addView(user_acc);
                        tr.addView(user_pwd);
                        user_list.addView(tr);


                    }
                } catch(Exception e) {
                    // Log.e("log_tag", e.toString());
                }
            }
        };
}
