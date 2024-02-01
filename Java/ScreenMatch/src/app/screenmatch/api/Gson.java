package app.screenmatch.api;

import com.google.gson.FieldNamingPolicy;
import com.google.gson.GsonBuilder;

public class Gson {
    private com.google.gson.Gson gson;

    public void inicializa(){
        this.gson = new GsonBuilder().setFieldNamingPolicy(FieldNamingPolicy.UPPER_CAMEL_CASE)
                .setPrettyPrinting()
                .create();
    }

    public com.google.gson.Gson getGson() {
        return gson;
    }

}
