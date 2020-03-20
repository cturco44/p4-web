#include <iostream>
#include "List.h"
#include "json.hpp"
#include <list>
#include <string>
#include <sstream>

using nlohmann::json;
using namespace std;

struct packet{
    string method;
    string path;
    string data;
};

int main() {

list<packet> queue;
packet datum;

while(cin >> datum.method >> datum.path)
{

    if(datum.method == "POST")
    {   
        string garbage;
        for(int i = 0; i < 8; ++i)
        {
             cin >> garbage;
        }

        json j;
        cin >> j;
        datum.data = j.dump(4);
    }

    if(datum.method == "GET")
    { 
        if(!queue.empty())
        {
            json temp;
            stringstream info(queue.front().data);
            info >> temp;

            cout << "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: ";
            cout << queue.front().data.size()<<endl<<endl;
            cout << temp;
        }
        else
        {
            cout << "HTTP/1.1 400 Bad Request\nContent-Type: application/json; charset=utf-8\nContent-Length: 0";
        } 
    }

}

}