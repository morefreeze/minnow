#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std;
class Reader;
class Writer;

class ByteStream
{
protected:
  uint64_t capacity_;
  // Please add any additional state to the ByteStream here, and not to the Writer and Reader interfaces.
  bool has_err_ { false };
  bool is_closed_ { false };
  char* buffer_;
  string peek_;
  uint64_t write_pos_ { 0 };
  uint64_t read_pos_ { 0 };

public:
  explicit ByteStream( uint64_t capacity );
  ~ByteStream();
  ByteStream( const ByteStream& other ) noexcept;            // 复制构造函数
  ByteStream& operator=( const ByteStream& other ) noexcept; // 赋值运算符
  ByteStream( ByteStream&& other ) noexcept;                 // 移动构造函数
  ByteStream& operator=( ByteStream&& other ) noexcept;      // 移动赋值运算符
  // Helper functions (provided) to access the ByteStream's Reader and Writer interfaces
  Reader& reader();
  const Reader& reader() const;
  Writer& writer();
  const Writer& writer() const;
};

class Writer : public ByteStream
{
public:
  void push( std::string data ); // Push data to stream, but only as much as available capacity allows.

  void close();     // Signal that the stream has reached its ending. Nothing more will be written.
  void set_error(); // Signal that the stream suffered an error.

  bool is_closed() const;              // Has the stream been closed?
  uint64_t available_capacity() const; // How many bytes can be pushed to the stream right now?
  uint64_t bytes_pushed() const;       // Total number of bytes cumulatively pushed to the stream
};

class Reader : public ByteStream
{
public:
  std::string_view peek() const; // Peek at the next bytes in the buffer
  void pop( uint64_t len );      // Remove `len` bytes from the buffer

  bool is_finished() const; // Is the stream finished (closed and fully popped)?
  bool has_error() const;   // Has the stream had an error?

  uint64_t bytes_buffered() const; // Number of bytes currently buffered (pushed and not popped)
  uint64_t bytes_popped() const;   // Total number of bytes cumulatively popped from stream
};

/*
 * read: A (provided) helper function thats peeks and pops up to `len` bytes
 * from a ByteStream Reader into a string;
 */
void read( Reader& reader, uint64_t len, std::string& out );
#define DEBUG( x )                                                                                                 \
  do {                                                                                                             \
    std::cerr << __FILE__ << ":" << __LINE__ << " " << __func__ << ":" << #x << ": " << ( x ) << std::endl;        \
  } while ( 0 )
// #define DEBUG(x) do { } while (0)