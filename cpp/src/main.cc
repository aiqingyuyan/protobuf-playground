#include <iostream>
#include <fstream>
#include <string>
#include "article_collection.pb.h"

using namespace std;

void PromptForArticle(tutorial::Article* article) {
        cout << "Enter article ID number: ";
        int id;
        cin >> id;
        article->set_id(id);
        cin.ignore(256, '\n');

        cout << "Enter article title: ";
        getline(cin, *article->mutable_title());

        cout << "Enter snippet: ";
        getline(cin, *article->mutable_snippet());

        cout << "Enter content: ";
        getline(cin, *article->mutable_content());

        cout << "Is this article featured? (yes/no): ";
        string answer;
        cin >> answer;
        if (answer == "yes") {
            article->set_isfeatured(true);
        } else {
            article->set_isfeatured(false);
        }

        tutorial::Article::Author *author = new tutorial::Article::Author();

        cout << "Enter author id: ";
        cin >> id;
        author->set_id(id);
        cin.ignore(256, '\n');

        cout << "Enter author name: ";
        getline(cin, *author->mutable_name());

        cout << "Enter author email: ";
        getline(cin, *author->mutable_email());

        article->set_allocated_author(author);

        while (true) {
            cout << "Enter a topic (Science/Technology/Nature/Entertainment/Politics): ";
            string topic;
            getline(cin, topic);

            if (topic.empty()) {
                break;
            }

            if (topic == "Science") {
                article->add_topic(tutorial::Article::SCIENCE);
            } else if (topic == "Technology") {
                article->add_topic(tutorial::Article::TECHNOLOGY);
            } else if (topic == "Nature") {
                article->add_topic(tutorial::Article::NATURE);
            } else if (topic == "Entertainment") {
                article->add_topic(tutorial::Article::ENTERTAINMENT);
            } else if (topic == "Politics") {
                article->add_topic(tutorial::Article::POLITICS);
            }
        }
}

void ListOfArticle(const tutorial::ArticleCollection& articleCollection) {
    for (int i = 0; i < articleCollection.article_size(); ++i) {
        const tutorial::Article& article = articleCollection.article(i);
        
        cout << "Article ID: " << article.id() << endl;
        cout << "  Title: " << article.title() << endl;
        cout << "  Snippet: " << article.snippet() << endl;
        cout << "  Content: " << article.content() << endl;
        cout << "  Featured? " << (article.isfeatured() ? "yes" : "no") << endl;

        cout << "  Author id: " << article.author().id() << endl;
        cout << "  Author name: " << article.author().name() << endl;
        cout << "  Author email: " << article.author().email() << endl;

        cout << "  Topics: ";
        for (int j = 0; j < article.topic_size(); ++j) {
            tutorial::Article::Topic topic = article.topic(j);

            switch(topic) {
                case tutorial::Article::SCIENCE:
                    cout << "Science ";
                    break;
                case tutorial::Article::TECHNOLOGY:
                    cout << "Technology ";
                    break;
                case tutorial::Article::NATURE:
                    cout << "Nature ";
                    break;
                case tutorial::Article::ENTERTAINMENT:
                    cout << "Entertainment ";
                    break;
                case tutorial::Article::POLITICS:
                    cout << "Politics ";
                    break;
                default:
                    continue;
            }
        }

        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " Article_Collection_File" << endl;
        return -1;
    }

    tutorial::ArticleCollection articleCollection;

    {
        // Read existing article collection file if it exists
        ifstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << ": File not found. Creating a new file." << endl;
        } else if (!articleCollection.ParseFromIstream(&input)) {
            cerr << "Failed to parse article collection file." << endl;
        }
    }

    // add an article
    PromptForArticle(articleCollection.add_article());

    {
        ofstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!articleCollection.SerializeToOstream(&output)) {
            cerr << "Failed to write article collection file." << endl;
            return -1;
        }
    }

    ListOfArticle(articleCollection);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}