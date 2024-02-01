package app.screenmatch.api;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class Http {
    private HttpClient client;
    private HttpRequest request;

    public void client(){
        this.client = HttpClient.newHttpClient();
    }

    public void request(String pesquisa){
        pesquisa = pesquisa.replaceAll(" ", "+"); //Troca espaços por "+"

        String url = "http://www.omdbapi.com/?t=" + pesquisa + "&apikey=506e6091";

        this.request = HttpRequest.newBuilder().uri(URI.create(url)).build();
    }


    public String response() throws IOException, InterruptedException {
        HttpResponse<String> response = client
                .send(request, HttpResponse.BodyHandlers.ofString());

        return response.body();
    }



}
