/*
Author: John Furlong
Date: June 12, 2020
Description: Chat Server
    Explain how you would design a chat server. In particular, provide details about the various backend components, classes, and methods.
    What would be the hardest problem to solve?

    One design for a chat server:

    struct User{
        int userID;
        string name;
        vector<User> friends;
        map<int, vector<string>> userID_to_messages;
    };
    
    class ChatServer{
        private:
            vector<User> users;

        public:
            ChatServer(vector<User> initial_users){
                users = initial_users
            }

            void addUser(User new_user){
                users.push_back(new_user);
            }

            void addFriend(int userID, User friend){
                users[userID].friend.push_back(friend);
            } 

            void send_message(int from, User to, string message){
                to.userID_to_messages[from].push_back(message);
            }

            // The hardest part of the implementation would be maintaining a database to store messages between users.
    };
*/

