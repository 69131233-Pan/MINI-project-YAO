#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// โครงสร้างข้อมูลสำหรับเก็บข้อมูลผู้ใช้ 1 คน
struct User {
    string username;
    string password;
};

// โครงสร้างข้อมูลสำหรับเก็บรายละเอียดกิจกรรม
struct Event {
    string category; // หมวดหมู่
    string detail;   // รายละเอียด
    string date;     // วันที่ (YYYY-MM-DD)
    string time;     // เวลา (HH:MM)
};

// ตัวแปรแบบ Global สำหรับเก็บรายชื่อผู้ใช้ทั้งหมดในระบบ
vector<User> users;

// ตัวแปร Global สำหรับเก็บรายการกิจกรรมทั้งหมด
vector<Event> eventList;

// ฟังก์ชันสำหรับสร้างบัญชีผู้ใช้ใหม่
void createAccount() {
    string newUsername, newPassword;
    cout << "\n--- สมัครสมาชิก ---" << endl;
    cout << "กรอกชื่อผู้ใช้: ";
    cin >> newUsername;

    // วนลูปเช็คผู้ใช้ทีละคนใน vector เพื่อดูว่าชื่อผู้ใช้ซ้ำหรือไม่
    for (const auto& u : users) {
        if (u.username == newUsername) {
            cout << "ชื่อผู้ใช้นี้มีในระบบแล้ว! กรุณาใช้ชื่ออื่น" << endl;
            return;
        }
    }

    cout << "กรอกรหัสผ่าน: ";
    cin >> newPassword;

    // สร้างข้อมูล User ใหม่ แล้วใส่ต่อท้ายลงใน vector users
    users.push_back({newUsername, newPassword});
    cout << "สมัครสมาชิกสำเร็จ!" << endl;
}

// 2. ฟังก์ชันเข้าสู่ระบบ (ถ้าผิดครบ 3 ครั้งจะปิดโปรแกรมอัตโนมัติ)
bool login() {
    string inputUser, inputPass;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    // ตรวจสอบว่าในระบบมีผู้ใช้สมัครไว้หรือยัง
    if (users.empty()) {
        cout << "\nยังไม่มีบัญชีในระบบ! กรุณาสมัครสมาชิกก่อน" << endl;
        return false;
    }

    // วนลูปรับค่าจนกว่าจะถูกต้อง หรือครบจำนวนครั้งสูงสุด
    while (attempts < MAX_ATTEMPTS) {
        cout << "\n--- เข้าสู่ระบบ ---" << endl;
        cout << "Username: ";
        cin >> inputUser;
        cout << "Password: ";
        cin >> inputPass;

        for (const auto& u : users) {
            if (u.username == inputUser && u.password == inputPass) {
                cout << "\nเข้าสู่ระบบสำเร็จ! ยินดีต้อนรับ " << inputUser << endl;
                return true;
            }
        }
        attempts++;
        cout << "ชื่อผู้ใช้หรือรหัสผ่านไม่ถูกต้อง! (ลองไปแล้ว ";
        cout << attempts << "/" << MAX_ATTEMPTS << " ครั้ง)" << endl;
    }

    // หากพิมพ์ผิดครบ 3 ครั้ง ระบบจะปิดตัวลง
    cout << "\nคุณพิมพ์ผิดเกิน 3 ครั้ง! ปิดโปรแกรมอัตโนมัติ..." << endl;
    exit(0);
}

// 3. ฟังก์ชันเพิ่มกิจกรรมใหม่
void addEvent() {
    Event newEvent;

    cout << "\n--- เพิ่มกิจกรรมใหม่ ---" << endl;
    cout << "หมวดหมู่: ";
    cin >> newEvent.category;
    cin.ignore(); // ล้างขยะใน Keyboard buffer
    cout << "รายละเอียด: ";
    getline(cin, newEvent.detail); // รับข้อความที่มีช่องว่างได้

    cout << "วันที่ (YYYY-MM-DD): ";
    cin >> newEvent.date;

    cout << "เวลา (HH:MM): ";
    cin >> newEvent.time;

    eventList.push_back(newEvent); // บันทึกลง vector
    cout << "เพิ่มกิจกรรมสำเร็จ!" << endl;
}

// 4. ฟังก์ชันแสดงกิจกรรมทั้งหมด
void displayAllEvents() {
    // ตรวจสอบว่ายังไม่มีกิจกรรมหรือไม่
    if (eventList.empty()) {
        cout << "\nยังไม่มีกิจกรรมที่บันทึกไว้" << endl;
        return;
    }

    cout << "\n--- กิจกรรมทั้งหมด ---" << endl;

    // นำกิจกรรมออกจาก eventList มาแสดงทีละรายการ
    for (const Event& oneEvent : eventList) {
        cout << "หมวดหมู่: " << oneEvent.category << endl;
        cout << "รายละเอียด: " << oneEvent.detail << endl;
        cout << "วันที่: " << oneEvent.date << endl;
        cout << "เวลา: " << oneEvent.time << endl;
        cout << "------------------------------" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n===============================" << endl;
        cout << "   ระบบแจ้งเตือนกิจกรรม (Event Reminder)" << endl;
        cout << "===============================" << endl;
        cout << "1. เข้าสู่ระบบ (Login)" << endl;
        cout << "2. สมัครสมาชิกใหม่ (Register)" << endl;
        cout << "3. ออกจากโปรแกรม" << endl;
        cout << "เลือกเมนู: ";
        cin >> choice;

        if (choice == 1) {
            if (login()) {
                cout << "\n>>> ยินดีต้อนรับเข้าสู่ระบบหลัก <<<\n";
                addEvent();
                displayAllEvents();
                break;
            }
        } else if (choice == 2) {
            createAccount();
            addEvent();
            displayAllEvents();
            break;
        } else if (choice == 3) {
            cout << "ขอบคุณที่ใช้งาน!" << endl;
            break;
        } else {
            cout << "ตัวเลือกไม่ถูกต้อง กรุณาเลือกใหม่อีกครั้ง" << endl;
        }
    }

    while (true) {
        cout << "\n===============================" << endl;
        cout << "         เมนูจัดการกิจกรรม" << endl;
        displayAllEvents();
        cout << "===============================" << endl;
        cout << "1. เพิ่มกิจกรรมใหม่ (addEvent)" << endl;
        cout << "2. เลือกแสดงเฉพาะวันที่เลือก (displayByDate)" << endl;
        cout << "3. ออกจากโปรแกรม" << endl;
        cout << "เลือกเมนู: ";
        cin >> choice;

        if (choice == 1) {
            addEvent();
        } else if (choice == 2) {
            cout << "โปรดระบุวัน (เช่น 2569-09-25)" << endl;
            break;
        } else if (choice == 3) {
            cout << "ออกจากระบบ ขอบคุณที่ใช้งาน!" << endl;
            break;
        } else {
            cout << "ตัวเลือกไม่ถูกต้อง กรุณาเลือกใหม่อีกครั้ง" << endl;
        }
    }

    return 0;
}
