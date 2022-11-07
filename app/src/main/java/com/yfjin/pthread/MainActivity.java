package com.yfjin.pthread;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import com.yfjin.pthread.databinding.ActivityMainBinding;


public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("pthreadJni");
    }

    private ActivityMainBinding binding;

    public static void jump(Context c) {
        c.startActivity(new Intent(c, MainActivity.class));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.fab.setOnClickListener(v -> test("s"));
    }

    private native void test(String b);

    public void onResultShow(int result) {
        Log.i("123123java", "result:" + result);
        runOnUiThread(() -> {
            binding.fab.setText("result:" + result);
        });
    }

}