#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  const Address http_server(host, "http");
    TCPSocket http_sock;
    http_sock.connect(http_server);
    string req_str;
    req_str += "GET " + path + " HTTP/1.1\r\n";
    req_str += "Host: " + host + "\r\n";
    req_str += "Connection: close\r\n";
    req_str += "\r\n";
    cerr << "request line: " << req_str << endl;
    http_sock.write(req_str);
    string buf;
    while (1) {
        http_sock.read(buf);
        if (buf.size() > 0) {
            cout << buf;
        } else {
            break;
        }
    };
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
