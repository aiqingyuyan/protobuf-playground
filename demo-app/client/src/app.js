import React, { Component } from 'react';
import axios from "axios";
import protobuf from "protobufjs";

import './app.css';

import ArticleCard from "./components/article-card";
import ArticleDetail from "./components/article-detail";

class App extends Component {

  ArticleCollection;

  constructor(props) {
    super(props);

    this.state = {
      articles: [],
      selectedArticle: null
    }
  }

  componentDidMount() {
    this.loadMessageDef();
    this.loadArticles();
  }

  async loadMessageDef() {
    try {
      // load protobuf messages definitions
      const root = await protobuf.load("article_collection.proto");

      // obtain message type
      this.ArticleCollection = root.lookupType("tutorial.ArticleCollection");
    } catch (err) {
      console.error(err);
    }
  }

  async loadArticles() {
    try {
      const response = await axios.get("http://localhost:5000/api/articles", {
        responseType: "arraybuffer"
      });

      // decode encoded data received from server
      const articleCollection = this.ArticleCollection.decode(new Uint8Array(response.data));
      this.setState({articles: articleCollection.articles});
    } catch (err) {
      console.error(err);
    }
  }

  renderArticles() {
    return this.state.articles.map((article) => {
      return (
        <ArticleCard key={article.id} article={article} onArticleSelected={(article) => { this.setState({selectedArticle: article}); }} />
      );
    });
  }

  render() {
    if (this.state.articles.length === 0) {
      return <div>Loading...</div>;
    }

    return (
      <div className="App">
        <header className="App-header">
          <h1 className="App-title">Welcome to Protobuf Playground</h1>
        </header>
       
        <div className="container">
          <div className="row">
            <div className="col-md-3">
              {this.renderArticles()}
            </div>
            <div className="col-md-9">
              <ArticleDetail selectedArticle={this.state.selectedArticle} />
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default App;
