#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

int width = 19;

void leaky(int ticks,int  max_arrival_rate,int  max_packet_size,int  max_queue_size,int  departure_rate, int curr_packet = -1) {
    cout << "Tick#\t" << setw(width) << "Arrived packets" << setw(width) << "Departed packets" << setw(width) << "Dropped packets" << setw(width) << "Packets in queue" << endl;
    queue<int> packets;
    for(int tick = 1; tick <= ticks; tick++) {
        int dropped = 0;
        int arrival = (rand() % max_arrival_rate);
        if(packets.size() + arrival > max_queue_size)
            dropped = max_queue_size - (int)packets.size() + arrival;
        for(int i = 0; i < arrival && packets.size() < max_queue_size; i++) {
            int packet = (rand() % max_packet_size) + 1;
            packets.push(packet);
        }
        int departed = 0;
        int bytes = rand() % departure_rate + 1;
        int curr_packet = packets.front();
        while(curr_packet <= bytes && !packets.empty()) {
            bytes -= curr_packet;
            packets.pop();
            departed++;
            if(packets.empty()) {
                curr_packet = -1;
                break;
            }
            curr_packet = packets.front();
        }
        if(curr_packet != -1 && bytes)
            packets.front() -= bytes;
        cout << tick << setw(width) << arrival << setw(width) << departed << setw(width) << dropped << setw(width) << packets.size() << endl;
    }
}



void token(int ticks,int  max_arrival_rate,int  max_packet_size,int  max_queue_size,int  token_rate,int  bucket_capacity) {
    cout << "Tick#\t" << setw(width) << "Arrived packets" << setw(width) << "Departed packets" << setw(width) << "Dropped packets" << setw(width) << "Packets in queue" << endl;
    queue<int> packets;
    int bucket = 0;
    for(int tick = 1; tick <= ticks; tick++) {
        int dropped = 0;
        int arrival = (rand() % max_arrival_rate);
        bucket += token_rate;
        if(packets.size() + arrival > max_queue_size)
            dropped = max_queue_size - (int)packets.size() + arrival;
        for(int i = 0; i < arrival && packets.size() < max_queue_size; i++) {
            int packet = (rand() % max_packet_size) + 1;
            packets.push(packet);
        }
        int departed = 0;
        int curr_packet = packets.front();
        while(curr_packet <= bucket && !packets.empty()) {
            bucket -= curr_packet;
            packets.pop();
            departed++;
            if(packets.empty()) {
                curr_packet = -1;
                break;
            }
            curr_packet = packets.front();
        }
        cout << tick << setw(width) << arrival << setw(width) << departed << setw(width) << dropped << setw(width) << packets.size() << endl;
    }
}

int main() {
    int ticks = 5;
    cout << "Choose an algorithm to run (0: Leaky bucket, 1:Token bucket):" << endl;
    int option;
    cin >> option; 
    if(!option) {
        cout << "Maximum packet arrival rate: " << endl;
        int max_arrival_rate;
        cin >> max_arrival_rate;
        cout << "Maximum packet size: " << endl;
        int max_packet_size;
        cin >> max_packet_size;
        cout << "Size of the queue: " << endl;
        int max_queue_size;
        cin >> max_queue_size;
        cout << "Departure Rate: " << endl;
        int departure_rate;
        cin >> departure_rate;
        leaky(ticks, max_arrival_rate, max_packet_size, max_queue_size, departure_rate);
    }
    else if(option == 1) {
        cout << "Maximum packet arrival rate: " << endl;
        int max_arrival_rate;
        cin >> max_arrival_rate;
        cout << "Maximum packet size: " << endl;
        int max_packet_size;
        cin >> max_packet_size;
        cout << "Size of the queue: " << endl;
        int max_queue_size;
        cin >> max_queue_size;
        cout << "Token rate: " << endl;
        int token_rate;
        cin >> token_rate;
        cout << "Bucket capacity: " << endl;
        int bucket_capacity;
        cin >> bucket_capacity;
        token(ticks, max_arrival_rate, max_packet_size, max_queue_size, token_rate, bucket_capacity);
    }
    else {
        cout << "This is not an option please rerun the code :)" << endl;
    }

    return 0;
}