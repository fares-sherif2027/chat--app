#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User
{
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User()
    {
        // TODO: Implement default constructor
    }

    User(string uname, string pwd, string phone)
    {
        // TODO: Implement parameterized constructor
    }

    string getUsername() const
    {
        // TODO: Implement getter
        return "";
    }

    string getPhoneNumber() const
    {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return "";
    }

    string getLastSeen() const
    {
        // TODO: Implement getter
        return "";
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
    }

    void setPhoneNumber(string phone)
    {
        // TODO: Implement setter
    }

    void updateLastSeen()
    {
        // TODO: Implement last seen update
    }

    bool checkPassword(string pwd) const
    {
        // TODO: Implement password check
        return false;
    }

    void changePassword(string newPwd)
    {
        // TODO: Implement password change
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

public:
    Message()
    {
        // TODO: Implement default constructor
    }

    Message(string sndr, string cntnt)
    {
        // TODO: Implement parameterized constructor
    }

    string getContent() const
    {
        // TODO: Implement getter
        return "";
    }

    string getSender() const
    {
        // TODO: Implement getter
        return "";
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return "";
    }

    Message* getReplyTo() const
    {
        // TODO: Implement getter
        return nullptr;
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
    }

    void setReplyTo(Message* msg)
    {
        // TODO: Implement setter
    }

    void updateTimestamp()
    {
        // TODO: Implement timestamp update
    }

    void display() const
    {
        // TODO: Implement message display
    }

    void addEmoji(string emojiCode)
    {
        // TODO: Implement emoji support
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        // TODO: Implement default constructor
        chatName = "";
    }

    Chat(vector<string> users, string name)
    {
        // TODO: Implement parameterized constructor
        participants = users;
        chatName = name;
    }

    void addMessage(const Message& msg)
    {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username)
    {

        if (index < 0 || index >= messages.size())
        {
            return false;
        }

        if (messages[index].getSender() == username)
        {
            messages.erase(messages.begin() + index);
            cout << username << " deleted the message" << endl;
            return true;
        }
        return false;
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
        for (int i = 0; i < messages.size(); i++)
        {
            cout << messages[i].getSender() << ": " << messages[i].getContent() << "[ " << messages[i].getTimestamp() << "]" << endl;
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        // TODO: Implement message search
        vector<Message> found;

        for (int i = 0; i < messages.size(); i++)
        {
            string content = messages[i].getContent();
            if (content.find(keyword) != string::npos) // npos here means not found like when we return -1
            {
                found.push_back(messages[i]);
            }
        }
        if (found.size() == 0)
        {
            found.push_back(Message("System", "No results found")); // here the system replies when there are no found results,the first parameter is sender and second is content
        }
        return found;
    }

    void exportToFile(const string& filename) const
    {
        // TODO: Implement export to file
        cout << " BEGIN FILE: " << filename << endl;

        for (int i = 0; i < messages.size(); ++i)
        {
            cout << messages[i].getSender() << ": " << messages[i].getContent() << "\n";
        }

        cout << " END FILE: " << filename << endl;
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        user1 = u1;
        user2 = u2;
    }

    void displayChat() const override
    {
        for (int i = 0; i < messages.size(); i++)
        {
            cout << i << "    :   " << messages[i].getSender() << "    " << messages[i].getContent() << "    " << messages[i].getTimestamp() << endl;
        }
    }

    void showTypingIndicator(const string& username) const
    {
        cout << username << " is typing..." << endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string& admin, const string& userToRemove)
    {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc)
    {
        // TODO: Implement set description
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string& username)
    {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
            {
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const
    {
        if (currentUserIndex == -1)
        {
            return false;
        }
        return true;
    }

    string getCurrentUsername() const
    {
        if (currentUserIndex != -1)
        {
            return users[currentUserIndex].getUsername();
        }
        return "";
    }


public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
    }

    void login()
    {
        // TODO: Implement user login
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
    }

    void createGroup()
    {
        // TODO: Implement group creation
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
    }

    void logout()
    {
        // TODO: Implement logout
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
