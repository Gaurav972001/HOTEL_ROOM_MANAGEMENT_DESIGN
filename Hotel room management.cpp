#include <bits/stdc++.h>
#define maxRoomEachCatergory 40
using namespace std;
class hotel
{
private:
    //<roomNo,{avail, reason, checkinDate, occupancy, price}>
    map<string, vector<string>> rooms;
    //<{cate, roomNo},{occupancy, checkoutDate, price}}
    map<pair<string, string>, vector<string>> bookedRoomsInfo;
    //<category, bookedRoomsCount>
    map<string, int> bookedRoomsCount;
    // totalRoomsAvailable
    int totalRooms;

public:
    hotel()
    {
        totalRooms = maxRoomEachCatergory * 3;
    }
    void createRooms(string s, vector<string> roomPrice)
    {
        for (int i = 0; i < s.size(); i++)
        {
            for (int j = 1; j <= maxRoomEachCatergory; j++)
            {
                if (j % 2 == 0)
                    rooms[to_string(j) + s[i]] = {"Yes", "-", "-", "-", "Single", roomPrice[i]};
                else
                    rooms[to_string(j) + s[i]] = {"Yes", "-", "-", "-", "Double", roomPrice[i]};
            }
        }
    }
    void bookRooms(string s, string roomNumber, string occupancy, string date, string price)
    {
        if (bookedRoomsCount[s] == maxRoomEachCatergory)
        {
            cout << "Sorry no room available in this category" << endl;
            return;
        }
        string checkindt = curDate();
        rooms[roomNumber] = {"No", "Booked", checkindt, date, occupancy, price};
        bookedRoomsInfo[{s, roomNumber}] = {occupancy, date, price};
        bookedRoomsCount[s]++;
        totalRooms--;
    }
    void displayRooms()
    {
        for (auto room : bookedRoomsCount)
        {
            if (room.second == 40)
                cout << "No of Available rooms in " << room.first << "->" << 0 << endl;
            else
                cout << "No of Available rooms in " << room.first << "->" << maxRoomEachCatergory - room.second << endl;
        }
    }
    void displayBookedRooms()
    {
        for (auto r : bookedRoomsInfo)
        {
            cout << "Catergory-" << r.first.first << " Room Number-" << r.first.second << " Occupancy-" << r.second[0] << " Date-" << r.second[1] << " Price-" << r.second[2] << endl;
        }
    }
    void displayCheckoutToday()
    {
        bool flag = false;
        for (auto i : bookedRoomsInfo)
        {
            if (i.second[1] == curDate())
            {
                flag = true;
                cout << i.first.second << "  ";
            }
        }
        if (!flag)
            cout << "No checkout today.." << endl;
    }
    void markAvailable(string rn)
    {
        if (!rooms.count(rn))
        {
            cout << "Room not found" << endl;
            return;
        }
        if (rooms[rn][0] == "Yes")
        {
            cout << "Room is already available" << endl;
            return;
        }
        if (rn[rn.size() - 1] == 'G')
        {
            bookedRoomsInfo.erase({"Garden View", rn});
            bookedRoomsCount["Garden View"]--;
        }
        else if (rn[rn.size() - 1] == 'N')
        {
            bookedRoomsInfo.erase({"Non AC", rn});
            bookedRoomsCount["Non AC"]--;
        }
        else
        {
            bookedRoomsInfo.erase({"AC", rn});
            bookedRoomsCount["AC"]--;
        }
        totalRooms++;

        rooms[rn][0] = "Yes";
        rooms[rn][1] = "-";
        rooms[rn][2] = "-";
        rooms[rn][3] = "-";
    }
    void markUnavailable(string rn, string checkoutdate, string reason)
    {
        if (!rooms.count(rn))
        {
            cout << "Room not found" << endl;
            return;
        }
        if (rooms[rn][0] == "Yes")
        {
            if (rn[rn.size() - 1] == 'G')
            {
                // occupancy, checkoutDate, price
                bookedRoomsInfo[{"Garden View", rn}] = {rooms[rn][4], checkoutdate, rooms[rn][5]};
                bookedRoomsCount["Garden View"]++;
            }
            else if (rn[rn.size() - 1] == 'N')
            {
                bookedRoomsInfo[{"Non AC", rn}] = {rooms[rn][4], checkoutdate, rooms[rn][5]};
                bookedRoomsCount["Non AC"]++;
            }
            else
            {
                bookedRoomsInfo[{"AC", rn}] = {rooms[rn][4], checkoutdate, rooms[rn][5]};
                bookedRoomsCount["AC"]++;
            }
            totalRooms--;
        }
        rooms[rn][0] = "No";
        rooms[rn][1] = reason;
        rooms[rn][2] = curDate();
        rooms[rn][3] = checkoutdate;
    }
    void totalRoomsAvailable()
    {
        cout << "Total number of room available are " << totalRooms;
    }
    string curDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string s = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        // cout<<s<<endl;
        return s;
    }
};

void bookRandomRooms(hotel &obj)
{
    vector<string> roomCat{"Garden View", "AC", "Non AC"};
    vector<string> roomPrice{"1800", "2000", "1000"};
    for (int i = 0; i < roomCat.size(); i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (j % 2 == 0)
                obj.bookRooms(roomCat[i], to_string(j) + roomCat[i][0], "Single", to_string(j % 32) + "/11/2021", roomPrice[i]);
            else
            {
                string checkInDt = obj.curDate();
                obj.bookRooms(roomCat[i], to_string(j) + roomCat[i][0], "Double", checkInDt, roomPrice[i]);
            }
        }
    }
}

int main()
{
    hotel obj;
    vector<string> roomPrice{"1800", "2000", "1000"};
    obj.createRooms("GNA", roomPrice);
    bookRandomRooms(obj);
    while (true)
    {
        cout << "1.View rooms available\n2.View rooms booked\n3.View rooms having checkout today\n4.Mark room as available\n5.Mark room as unavailable\n6.Total rooms available\n\nPress 0 to exit...\n\n";
        int option;
        cin >> option;

        switch (option)
        {
        case 0:
        {
            cout << "Bye..." << endl;
            exit(0);
            break;
        }
        case 1:
        {
            obj.displayRooms();
            break;
        }
        case 2:
        {
            obj.displayBookedRooms();
            break;
        }
        case 3:
        {
            obj.displayCheckoutToday();
            break;
        }
        case 4:
        {
            string roomNo;
            cout << "\nEnter room number: " << endl;
            cin >> roomNo;
            obj.markAvailable(roomNo);
            break;
        }
        case 5:
        {
            string roomNo;
            cout << "\nEnter room number: " << endl;
            cin >> roomNo;
            string reason;
            cout << "Enter reason: " << endl;
            cin >> reason;
            cout << "\nEnter checkout date format-dd:mm:yyyy: (Type '-' if under maintenance)" << endl;
            string checkoutdate;
            cin >> checkoutdate;
            obj.markUnavailable(roomNo, checkoutdate, reason);
            break;
        }
        case 6:
        {
            obj.totalRoomsAvailable();
            break;
        }
        default:
            cout << "Please select a valid option\n";
            break;
        }
        cout << "\n\n";
    }
}