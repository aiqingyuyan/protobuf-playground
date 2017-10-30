import random
import article_collection_pb2
from barnum import gen_data

""" Random generated data for demo """
names = [gen_data.create_name() for _ in range(0, 15)]
emails = [gen_data.create_email() for _ in range(0, 15)]
titles = [gen_data.create_nouns() for _ in range(0, 15)]
contents = [gen_data.create_paragraphs(8) for _ in range(0, 15)]

articles = []

""" Construct articles data """
for title in titles:
    content = random.choice(contents)
    name = random.choice(names)
    email = random.choice(emails)

    articles.append({
        "id": random.randint(10010, 20020),
        "title": title,
        "snippet": content[0:100],
        "content": content,
        "isFeatured": random.choice([False, True]),
        "topics": random.sample([0, 1, 2, 3, 4], 3),
        "author": {
            "id": random.randint(10010, 20020),
            "name": name[0] + " " + name[1],
            "email": email
        }
    })

def get_protobuf_data():
    """ Construct protobuf data """
    proto_articles = []
    for article in articles:
        proto_articles.append(article_collection_pb2.Article(
            id = article["id"],
            title = article["title"],
            snippet = article["snippet"],
            content = article["content"],
            isFeatured = article["isFeatured"],
            topics = article["topics"],
            author = article["author"]
        ))
    
    return article_collection_pb2.ArticleCollection(articles = proto_articles)

# print get_protobuf_data()