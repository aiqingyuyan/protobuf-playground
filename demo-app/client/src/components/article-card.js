import React, { Component } from "react";

import "./article-card.css"

export default class ArticleCard extends Component {
    render() {
        const article = this.props.article;
        const onArticleSelected = this.props.onArticleSelected;

        return (
            <div className="card"
                 onClick={() => {onArticleSelected(article)}}>
                <div className="card-body">
                    <h4 className="card-title">
                        {article.title}
                    </h4>
                    <h6 className="card-subtitle mb-2 text-muted">
                        {article.author.name}
                    </h6>
                    <p className="card-text">{article.snippet}</p>
                </div>
            </div>
        );
    }
}
