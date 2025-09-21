package main

import (
    "encoding/json"
    "fmt"
    "io/ioutil"
    "net/http"
    "os"
)

type Article struct {
    Title  string `json:"title"`
    Source struct {
        Name string `json:"name"`
    } `json:"source"`
    URL string `json:"url"`
}

type NewsResponse struct {
    Status  string    `json:"status"`
    Total   int       `json:"totalResults"`
    Articles []Article `json:"articles"`
}

func main() {
    apiKey := "3ed1bbf4495c45dc9a188662c8e41fae" // get free key from https://newsapi.org/
    url := "https://newsapi.org/v2/everything?q=AI&language=en&sortBy=publishedAt&pageSize=5&apiKey=" + apiKey

    resp, err := http.Get(url)
    if err != nil {
        fmt.Println("Error fetching news:", err)
        //os.Exit(1)
    }
    defer resp.Body.Close()

    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        fmt.Println("Error reading response:", err)
        os.Exit(1)
    }

    var news NewsResponse
    if err := json.Unmarshal(body, &news); err != nil {
        fmt.Println("Error parsing JSON:", err)
        os.Exit(1)
    }

    fmt.Println("Latest AI News:")
    for i, article := range news.Articles {
        fmt.Printf("%d. %s - %s\n   %s\n\n", i+1, article.Title, article.Source.Name, article.URL)
    }
}
