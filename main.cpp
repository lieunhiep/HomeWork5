#include<iostream>
#include<vector>
#include<string>
using namespace std;

// ================= VEHICLES =================
// Lớp phương tiện chung
class Vehicles {
protected:
    string route;
    int capacity;
    bool status; //true: đúng giờ, false: trễ
public:
    // Hàm khởi tạo
    Vehicles(string _route, int _capacity, bool _status) {
        route = _route;
        capacity = _capacity;
        status = _status;
    }
    // Hàm in thông tin
    virtual void displayInfo() {
        cout << "Vehicle - Route: " << route
        << ", Capacity: " << capacity
        << ", Status: " << (status ? "On-time" : "Delayed") << '\n';
    }
};

// ================= BUS =================
// Lớp xe bus, kế thừa từ Vehicles
class Bus : public Vehicles {
protected:
    double speed = 40; // giả sử tốc độ xe bus thường là 40 Km/h
public:
    // Hàm khởi tạo
    Bus(string _route, int _capacity, bool _status)
    : Vehicles(_route, _capacity, _status) {}
    
    // Ghi đè hàm hiển thị thông tin
    void displayInfo() override {
        cout << "Bus - Route: \n";
        Vehicles :: displayInfo();
    }

    // Hàm tính thời gian di chuyển
    virtual double calculateTravelTime(double distance) {
        return distance / speed;
    }
};

// ================= EXPRESS BUS =================
// Lớp xe bus nhanh, kế thừa từ Bus
class ExpressBus : public Bus {
private:
    int fewerStops; // số điểm dừng ít hơn
public:
    // Hàm khởi tạo
    ExpressBus(string _route, int _capacity, bool _status, int _fewerStops)
    : Bus(_route, _capacity, _status), fewerStops(_fewerStops) {}
    
    // Ghi đè hàm tính thời gian di chuyển (nhanh hơn 20%)
    double calculateTravelTime(double distance) override {
        return distance / speed * 0.8;
    }
    
    // Ghi đè hàm hiển thị thông tin
    void displayInfo() override {
        cout << "Express Bus - Route: " << route
        << ", Capacity: " << capacity
        << ", Fewer Stops: " << fewerStops
        << ", Status: " << (status ? "On-time" : "Delayed") << '\n';
    }
};

// ================= STATIONS =================
// Lớp trạm (station)
class Stations {
private:
    string name;
    string location;
    string type; // loại trạm (bus/train)
    vector<string> scheduled; // danh sách lịch trình
    vector<Vehicles> vehicles; // danh sách phương tiện
public:
    // Hàm khởi tạo
    Stations(string _name, string _location, string _type, vector<string> _scheduled, vector<Vehicles> _vehicles) {
        name = _name;
        location = _location;
        type = _type;
        scheduled = _scheduled;
        vehicles = _vehicles;
    }
    // Thêm lịch trình
    void addScheduled(string s) {
        scheduled.push_back(s);
    }
    // Xóa lịch trình
    void removeScheduled(string s) {
        vector<string> tmp;
        for(int i=0;i<scheduled.size();i++) {
            if(s != scheduled[i]) {
                tmp.push_back(scheduled[i]);
            }
        }
        scheduled = tmp;
    }
    // Hiển thị thông tin trạm
    void displayInfo() {
        cout << "Station: " << name << " (" << type << ") at " << location << '\n';
        cout << "Schedules: \n";
        for (auto x : scheduled) cout << x << '\n';
    }
    // Gán phương tiện vào trạm
    void assignVehicle(Vehicles v) {
        vehicles.push_back(v);
    }
};

// ================= PASSENGER =================
// Lớp hành khách
class Passenger {
private:
    string name;
    string ID;
    string bookedTicket; // vé đã đặt
public:
    // Hàm khởi tạo
    Passenger(string _name, string _id){
        name = _name;
        ID = _id;
    }
    
    // Hiển thị thông tin hành khách
    void displayInfo() {
        cout << "Passenger: " << name << " (ID: " << ID << ")\n";
        if (bookedTicket != "")
            cout << "Booked ticket: " << bookedTicket << '\n';
        else
            cout << "No ticket booked.\n";
    }
    // Hành khách đặt vé
    void bookTicket(string ticketInfo) {
        bookedTicket = ticketInfo;
        cout << name << " booked ticket: " << bookedTicket << '\n';
    }
    
    // Hành khách hủy vé
    void cancelTicket() {
        if (bookedTicket != "") {
            cout << name << " canceled ticket: " << bookedTicket << '\n';
            bookedTicket = "";
        } else {
            cout << name << " has no ticket to cancel!\n";
        }
    }
};

// ================= MAIN =================
int main() {
    // Test Bus và ExpressBus
    cout << "=== Test Vehicles ===\n";
    Bus bus1("Route A", 40, true);
    ExpressBus exp1("Route B", 30, false, 3);
    bus1.displayInfo();
    cout << "Bus travel time (100 km): " << bus1.calculateTravelTime(100) << " hours\n";
    exp1.displayInfo();
    cout << "Express bus travel time (100 km): " << exp1.calculateTravelTime(100) << " hours\n";

    // Test Station
    cout << "\n=== Test Stations ===\n";
    vector<string> schedule = {"08:00 Arrival", "09:00 Departure"};
    vector<Vehicles> vehicles = {bus1};
    Stations st1("Central", "Downtown", "Bus", schedule, vehicles);
    st1.displayInfo();
    st1.addScheduled("10:00 Arrival");
    cout << "\nAfter adding schedule:\n";
    st1.displayInfo();
    st1.removeScheduled("09:00 Departure");
    cout << "\nAfter removing schedule:\n";
    st1.displayInfo();

    // Test Passenger
    cout << "\n=== Test Passenger ===\n";
    Passenger p1("Alice", "P001");
    Passenger p2("Bob", "P002");
    p1.displayInfo();
    p1.bookTicket("Route A - 08:00");
    p1.displayInfo();
    p1.cancelTicket();
    p1.displayInfo();

    p2.bookTicket("Route B - 09:00");
    p2.displayInfo();

    return 0;
}
