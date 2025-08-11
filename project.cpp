

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
        username = "";
        password = "";
        phoneNumber = "";
        status = "";
        lastSeen = "";
    }

    User(string uname, string pwd, string phone)
    {
        // TODO: Implement parameterized constructor
        username = uname;
        password = pwd;
        phoneNumber = phone;
    }

    string getUsername() const
    {
        // TODO: Implement getter
        return username;
    }

    string getPhoneNumber() const
    {
        // TODO: Implement getter
        return phoneNumber;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    string getLastSeen() const
    {
        // TODO: Implement getter
        return lastSeen;
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
        status = newStatus;
    }

    void setPhoneNumber(string phone)
    {
        // TODO: Implement setter
        phoneNumber = phone;
    }

    void updateLastSeen()
    {
        // TODO: Implement last seen update
        time_t now = time(0);
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        lastSeen = string(buffer);
    }

    bool checkPassword(string pwd) const
    {
        // TODO: Implement password check
        if (pwd == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void changePassword(string newPwd)
    {
        // TODO: Implement password change
        password = newPwd;
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
    Message *replyTo;

public:
    Message()
    {
        sender = "";
        content = "";
        timestamp = "";
        status = "";
    }

    Message(string sndr, string cntnt)
    {
        sender = sndr;
        content = cntnt;
    }

    string getContent() const
    {
        // TODO: Implement getter
        return content;
    }

    string getSender() const
    {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    Message *getReplyTo() const
    {
        // TODO: Implement getter
        return nullptr;
    }

    void setStatus(string newStatus)
    {
        status = newStatus;
    }

    void setReplyTo(Message *msg)
    {
        replyTo = msg;
    }

    void updateTimestamp()
    {
        time_t now = time(0);
        char buffer[26];                       // ctime_s requires at least 26 characters
        ctime_s(buffer, sizeof(buffer), &now); // safe version of ctime
        timestamp = buffer;
        if (!timestamp.empty() && timestamp.back() == '\n')
            timestamp.pop_back();
    }

    void display() const
    {
        cout << "sender:" << sender << "|" << "status:" << status << "|" << "timestamp:" << timestamp << "|" << "content:" << content << endl;
    }

    void addEmoji(int emojiCode)
    {
        if (emojiCode == 1)
            content += u8"\U0001F600"; // happy emoji
        else if (emojiCode == 2)
            content += u8"\U0001F602"; // sympathy emoji
        else if (emojiCode == 3)
            content += u8"\U0001F609"; // heart emoji
        else
            content += u8"\u2764";
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

    vector<Message> &getMessages()
    {
        return messages;
    }

    vector<string> &getParticipants()
    {
        return participants;
    }

    void addMessage(const Message &msg)
    {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
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

    void exportToFile(const string &filename) const
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

    string getUser1()
    {
        return user1;
    }

    string getUser2()
    {
        return user2;
    }

    void displayChat() const override
    {
        cout << "=== Private Chat: " << user1 + "   " + user2 << " ===" << endl;

        cout << endl;

        // Show messages
        cout << "Messages:" << endl;
        if (messages.empty())
        {
            cout << "(no messages yet)" << endl;
        }
        else
        {
            for (size_t i = 0; i < messages.size(); ++i)
            {
                cout << i << " : "
                     << messages[i].getSender()
                     << " : " << messages[i].getContent()
                     << " [" << messages[i].getTimestamp() << "]"
                     << endl;
            }
        }
    }

    void showTypingIndicator(const string &username) const
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
    GroupChat(vector<string> users, string name, string creator) : Chat(users, name)
    {
        bool found = false;
        for (int i = 0; i < participants.size(); ++i)
        {
            if (participants[i] == creator)
            {
                found = true;
                break;
            }
        }
        if (!found)
            participants.push_back(creator);

        admins.push_back(creator);
        description = "";
    }

    void addAdmin(string newAdmin)
    {
        if (!isParticipant(newAdmin))
        {
            cout << "Cannot make " << newAdmin << " an admin because they are not a participant." << endl;
            return;
        }
        if (isAdmin(newAdmin))
        {
            cout << newAdmin << " is already an admin." << endl;
            return;
        }
        admins.push_back(newAdmin);
        cout << newAdmin << " is now an admin." << endl;
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        if (!isAdmin(admin))
        {
            cout << admin << " is not an admin and cannot remove participants." << endl;
            return false;
        }

        if (admin == userToRemove)
        {
            cout << "Admin cannot remove themselves." << endl;
            return false;
        }

        int idx = -1;
        for (int i = 0; i < participants.size(); ++i)
        {
            if (participants[i] == userToRemove)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            cout << userToRemove << " is not a participant." << endl;
            return false;
        }

        participants.erase(participants.begin() + idx);

        for (int i = 0; i < admins.size(); ++i)
        {
            if (admins[i] == userToRemove)
            {
                admins.erase(admins.begin() + i);
                break;
            }
        }

        cout << userToRemove << " has been removed from the group by " << admin << "." << endl;
        return true;
    }

    bool isAdmin(string username) const
    {
        for (int i = 0; i < admins.size(); ++i)
        {
            if (admins[i] == username)
                return true;
        }
        return false;
    }

    bool isParticipant(string username) const
    {
        for (int i = 0; i < participants.size(); ++i)
        {
            if (participants[i] == username)
                return true;
        }
        return false;
    }

    void setDescription(string desc)
    {
        description = desc;
        cout << "Group description updated." << endl;
    }

    void displayChat() const override
    {
        cout << "=== Group: " << chatName << " ===" << endl;
        cout << "Description: " << (description.empty() ? "(no description)" : description) << endl;

        cout << "Participants (" << participants.size() << "): ";
        for (size_t i = 0; i < participants.size(); ++i)
        {
            cout << participants[i];
            if (i != participants.size() - 1)
                cout << ", ";
        }
        cout << endl;

        cout << "Admins (" << admins.size() << "): ";
        for (size_t i = 0; i < admins.size(); ++i)
        {
            cout << admins[i];
            if (i != admins.size() - 1)
                cout << ", ";
        }
        cout << endl;

        cout << "Messages:" << endl;
        if (messages.empty())
        {
            cout << "(no messages yet)" << endl;
        }
        else
        {
            for (size_t i = 0; i < messages.size(); ++i)
            {
                cout << (i + 1) << " : " << messages[i].getSender()
                     << " : " << messages[i].getContent()
                     << " [" << messages[i].getTimestamp() << "]" << endl;
            }
        }
    }

    void sendJoinRequest(const string &username)
    {
        if (isParticipant(username))
        {
            cout << username << " is already a participant." << endl;
            return;
        }

        participants.push_back(username);
        cout << username << " has joined the group (via join request)." << endl;
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
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
        string uname, pwd, phone;
        cout << "Enter username: ";
        cin >> uname;

        if (findUserIndex(uname) != -1)
        {
            cout << "Username already exists.\n";
            return;
        }

        cout << "Enter password: ";
        cin >> pwd;
        cout << "Enter phone number: ";
        cin >> phone;

        users.push_back(User(uname, pwd, phone));
        cout << "User registered successfully!\n";
    }

    void login()
    {
        string uname, pwd;
        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pwd;

        int index = findUserIndex(uname);
        if (index != -1 && users[index].checkPassword(pwd))
        {
            currentUserIndex = index;
            cout << "Login successful! Welcome, " << uname << ".\n";
        }
        else
        {
            cout << "Invalid username or password.\n";
        }
    }

    void startPrivateChat()
    {
        if (!isLoggedIn())
        {
            cout << "You must login in to start a private chat.\n";
            return;
        }

        string otherUser;
        cout << "Enter the username of the person to chat with: ";
        cin >> otherUser;

        if (findUserIndex(otherUser) == -1)
        {
            cout << "User not found.\n";
            return;
        }

        PrivateChat *newChat = new PrivateChat(getCurrentUsername(), otherUser);
        chats.push_back(newChat);

        cout << "Private chat started with " << otherUser << ".\n";
    }

    void createGroup()
    {
        if (!isLoggedIn())
        {
            cout << "You must login in to create a group.\n";
            return;
        }

        string groupName;
        cout << "Enter group name: ";
        cin.ignore();
        getline(cin, groupName);

        vector<string> members;
        members.push_back(getCurrentUsername());

        int numMembers;
        cout << "How many members to add? (don't count yourself): ";
        cin >> numMembers;

        for (int i = 0; i < numMembers; i++)
        {
            string member;
            cout << "Enter username of member " << i + 1 << ": ";
            cin >> member;

            if (findUserIndex(member) != -1)
            {
                members.push_back(member);
            }
            else
            {
                cout << "User " << member << " not found. Skipping.\n";
            }
        }

        GroupChat *group = new GroupChat(members, groupName, getCurrentUsername());
        chats.push_back(group);

        cout << "Group '" << groupName << "' created successfully!\n";
    }

    void viewChats() const
    {
        if (!isLoggedIn())
        {
            cout << "You must be logged in to view chats.\n";
            return;
        }

        string loggedInUser = users[currentUserIndex].getUsername();

        if (chats.empty())
        {
            cout << "No chats available.\n";
            return;
        }

        vector<int> visibleIndexes;
        cout << "Your chats:\n";
        int displayNum = 1;

        // Show only chats where the logged-in(currentUserIndex) user is in participants (group) or matches user1/user2 (private)
        for (int i = 0; i < chats.size(); i++)
        {
            bool showChat = false;

            if (GroupChat *groupChat = dynamic_cast<GroupChat *>(chats[i])) // pointer that checks if groupchat and return the chat if not return null
            {
                const vector<string> &participants = groupChat->getParticipants();
                bool found = false;
                for (int i = 0; i < participants.size(); i++)
                {
                    if (participants[i] == loggedInUser)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Error: User is not a participant in the group.\n";
                    break;
                }
                showChat = true;
            }
            else if (PrivateChat *privateChat = dynamic_cast<PrivateChat *>(chats[i])) // pointer that checks if privatechat and return the chat if not return null
            {
                if (privateChat->getUser1() == loggedInUser || privateChat->getUser2() == loggedInUser)
                    showChat = true;
            }

            if (showChat)
            {
                visibleIndexes.push_back(i); // its index is the visible index to user (but as 1-indexed) and the values are the actual index in chats
                cout << displayNum++ << ". ";
                chats[i]->displayChat();
                cout << "----------------------\n\n\n\n";
            }
        }

        if (visibleIndexes.empty())
        {
            cout << "You are not part of any chats.\n";
            return;
        }

        int choice;
        cout << "Choose chat by index or exit (0): ";
        cin >> choice;
        if (choice == 0)
            return;

        if (choice < 1 || choice > (int)visibleIndexes.size())
        {
            cout << "Invalid chat index.\n";
            return;
        }

        Chat *selectedChat = chats[visibleIndexes[choice - 1]]; // the user choose the visible index and it is called using the actual index in chats

        while (true)
        {
            bool isGroup = dynamic_cast<GroupChat *>(selectedChat) != nullptr; // checks if this chat is group(true) or private(false)
            bool isAdmin = false;

            if (isGroup)
            {
                GroupChat *groupChat = dynamic_cast<GroupChat *>(selectedChat);
                isAdmin = groupChat->isAdmin(loggedInUser);
            }

            cout << "\nOptions:\n";
            cout << "1- Add message\n";
            cout << "2- Delete message\n";

            // Group chat admin options
            if (isGroup && isAdmin) // only apppear if it is groupchat amd the user is admin and participant
            {
                cout << "3- Add Admin\n";
                cout << "4- Set Description\n";
                cout << "5- Remove Participant\n";
            }

            cout << "0- Exit\n";
            cout << "Choice: ";

            int menuChoice;
            cin >> menuChoice;

            if (menuChoice == 0)
                break;

            switch (menuChoice)
            {
            case 1:
            { // Add message
                string content;
                cout << "Enter message content: ";
                cin >> ws;
                getline(cin, content);

                Message newMsg(loggedInUser, content);
                newMsg.updateTimestamp();
                newMsg.setStatus("sent");
                selectedChat->addMessage(newMsg);

                cout << "Message added by " << loggedInUser << ".\n";
                break;
            }

            case 2:
            { // Delete message
                int msgIndex;
                cout << "Enter message index to delete: ";
                cin >> msgIndex;

                if (msgIndex < 0 || msgIndex >= (int)selectedChat->getMessages().size())
                {
                    cout << "Invalid message index.\n";
                }
                else
                {
                    const Message &msg = selectedChat->getMessages()[msgIndex];
                    bool canDelete = false;

                    if (!isGroup) // Not a group chat (delete message only if you were the sender)
                    {
                        if (msg.getSender() == loggedInUser)
                        {
                            canDelete = true;
                        }
                    }
                    else // It is a group chat (delete message if you were the sender or an admin)
                    {
                        if (msg.getSender() == loggedInUser || isAdmin)
                        {
                            canDelete = true;
                        }
                    }

                    if (canDelete)
                    {
                        selectedChat->deleteMessage(msgIndex, msg.getSender());
                        cout << "Message deleted.\n";
                    }
                    else
                    {
                        cout << "You don't have permission to delete this message.\n";
                    }
                }
                break;
            }

            case 3:
            { // Add admin
                if (isGroup && isAdmin)
                {
                    GroupChat *groupChat = dynamic_cast<GroupChat *>(selectedChat);
                    string newAdmin;
                    cout << "Enter username to add as admin: ";
                    cin >> ws;
                    getline(cin, newAdmin);

                    // Check if user exists in the system(users)
                    bool userExists = false;
                    for (const auto &user : users)
                    {
                        if (user.getUsername() == newAdmin)
                        {
                            userExists = true;
                            break;
                        }
                    }

                    if (!userExists)
                    {
                        cout << "Error: User does not exist.\n";
                        break;
                    }

                    // Check if the user is a participant in the group(so the user exists and a participant)
                    const vector<string> &participants = groupChat->getParticipants();
                    bool found = false;
                    for (int i = 0; i < participants.size(); i++)
                    {
                        if (participants[i] == newAdmin)
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        cout << "Error: User is not a participant in the group.\n";
                        break;
                    }
                    // {
                    //    cout << "Error: User is not a participant in the group.\n";
                    //  break;
                    //}

                    // Add admin
                    groupChat->addAdmin(newAdmin);
                    cout << "Admin added.\n";
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
                break;
            }

            case 4:
            { // Set description
                if (isGroup && isAdmin)
                {
                    GroupChat *groupChat = dynamic_cast<GroupChat *>(selectedChat);
                    string desc;
                    cout << "Enter new description: ";
                    cin >> ws;
                    getline(cin, desc);
                    groupChat->setDescription(desc);
                    cout << "Description set.\n";
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
                break;
            }

            case 5:
            { // Remove participant
                if (isGroup && isAdmin)
                {
                    GroupChat *groupChat = dynamic_cast<GroupChat *>(selectedChat);
                    string userToRemove;
                    cout << "Enter username to remove: ";
                    cin >> ws;
                    getline(cin, userToRemove);

                    if (groupChat->removeParticipant(loggedInUser, userToRemove))
                    {
                        cout << "Participant removed.\n";
                    }
                    else
                    {
                        cout << "Failed to remove participant (check user existence).\n";
                    }
                }
                else
                {
                    cout << "Invalid choice.\n";
                }
                break;
            }

            default:
                cout << "Invalid choice.\n";
            }
        }
    }

    void logout()
    {
        if (!isLoggedIn())
        {
            cout << "You are not logged in.\n";
            return;
        }
        cout << "User " << getCurrentUsername() << " logged out.\n";
        currentUserIndex = -1;
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
