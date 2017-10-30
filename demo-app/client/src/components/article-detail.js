import React, { Component } from "react";

export default class ArticleDetail extends Component {
    render() {
        const selectedArticle = this.props.selectedArticle;

        if (!selectedArticle) {
            return <div>Select an article from list to view</div>;
        }

        return (
            <div>
                <h2>{selectedArticle.title}</h2>
                <h6 className="text-center">
                    {selectedArticle.author.name}
                </h6>
                <div>
                    {selectedArticle.content}
                </div>
            </div>
        );
    }
}
