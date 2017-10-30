# protobuf-playground
  Repo for demoing how to use google protobuf
  ## cpp - a simple c++ console app using protobuf
  To run the app(in mac, 'brew install protobuf' first), go to the src folder: 
  
    1. run 'make' command in terminal, which will generate a console app named 'addressbook'
    
    2. in terminal, run ./addressbook <filename> to start the app, e.g. ./addressbook testfile
   
  ## demo-app - a simple python web service app using protobuf
   To run the app, you need to install a few python packages, cd to `demo-app/server`, and run `pip install -r requirements.txt`

   To start the entire demp app:

    1. cd to 'demo-app/server', run 'python app.py' to start dummy api server

    2. cd to 'demo-app/client', run 'npm start' to start dummy server serving static files

   Then you can start using postman (desktop version) to test the simple api endpoint, or go to `localost:8080` to play with the simple demo app.