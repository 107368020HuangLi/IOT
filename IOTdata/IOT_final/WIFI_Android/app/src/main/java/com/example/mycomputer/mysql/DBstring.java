package com.example.mycomputer.mysql;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;

import static org.apache.http.HttpEntity.*;

public class DBstring {
    public  static String DB1(String i){
        String result="";

        try{
            HttpClient HC = new DefaultHttpClient();
            HttpPost HP = new HttpPost("http://140.124.72.10/IOT/test.php");
            ArrayList<NameValuePair> params = new ArrayList<NameValuePair>();
            params.add(new BasicNameValuePair("",i));
            HP.setEntity(new UrlEncodedFormEntity(params, HTTP.UTF_8));
            HttpResponse HR = HC.execute(HP);

            /////////////////////////////
            HttpEntity httpEntity = HR.getEntity();
            InputStream inputStream = httpEntity.getContent();

            BufferedReader bufReader = new BufferedReader(new InputStreamReader(inputStream, "utf-8"), 8);
            StringBuilder builder = new StringBuilder();
            String line = null;
            while((line = bufReader.readLine()) != null) {
                builder.append(line + "\n");
            }
            inputStream.close();
            result = builder.toString();

            ////////////////////////////////////


        }catch(Exception e){
          //  Log.i("錯誤資訊:",e.toString());

        }

        return result;
    }
}
