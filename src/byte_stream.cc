#include <stdexcept>
#include <cstring>
#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
{
  buffer_ = allocator<char>().allocate(capacity_);
  peek_ = string(capacity, ' ');
}

ByteStream::ByteStream(const ByteStream& other)
  : capacity_(other.capacity_), has_err_(other.has_err_),
  is_closed_(other.is_closed_),
  write_pos_(other.write_pos_), read_pos_(other.read_pos_)
{
  DEBUG("copy");
  buffer_ = allocator<char>().allocate(capacity_);
  memcpy(buffer_, other.buffer_, capacity_);
  peek_ = other.peek_;
}

ByteStream& ByteStream::operator=(const ByteStream& other)
{
  DEBUG("op=");
  if (this != &other) {
    allocator<char>().deallocate(buffer_, capacity_);
    capacity_ = other.capacity_;
    has_err_ = other.has_err_;
    is_closed_ = other.is_closed_;
    buffer_ = allocator<char>().allocate(capacity_);
    memcpy(buffer_, other.buffer_, capacity_);
    peek_ = other.peek_;
    write_pos_ = other.write_pos_;
    read_pos_ = other.read_pos_;
  }
  return *this;
}

ByteStream::ByteStream(ByteStream&& other)
  : capacity_(other.capacity_), has_err_(other.has_err_),
  is_closed_(other.is_closed_), buffer_(other.buffer_), peek_(other.peek_),
  write_pos_(other.write_pos_), read_pos_(other.read_pos_)
{
  other.capacity_ = 0;
  other.buffer_ = nullptr;
}

ByteStream& ByteStream::operator=(ByteStream&& other)
{
  if (this != &other) {
    allocator<char>().deallocate(buffer_, capacity_);
    capacity_ = other.capacity_;
    has_err_ = other.has_err_;
    is_closed_ = other.is_closed_;
    buffer_ = other.buffer_;
    peek_ = other.peek_;
    write_pos_ = other.write_pos_;
    read_pos_ = other.read_pos_;
    other.capacity_ = 0;
    other.buffer_ = nullptr;
  }
  return *this;
}

ByteStream::~ByteStream() {
  DEBUG("des");
  allocator<char>().deallocate(buffer_, capacity_);
}

void Writer::push( string data )
{
  auto len = data.size();
  len = min(len, available_capacity());
  auto first_len = min(len, capacity_ - write_pos_ % capacity_);
  memcpy(buffer_ + (write_pos_ % capacity_), data.c_str(), first_len);
  if (len > first_len) {
    memcpy(buffer_, data.c_str() + first_len, len - first_len);
  }
  write_pos_ += len;
}

void Writer::close()
{
  is_closed_ = true;
}

void Writer::set_error()
{
  has_err_ = true;
}

bool Writer::is_closed() const
{
  return is_closed_;
}

uint64_t Writer::available_capacity() const
{
  return read_pos_ + capacity_ - write_pos_;
}

uint64_t Writer::bytes_pushed() const
{
  return write_pos_;
}

string_view Reader::peek() const
{
  auto read_left = capacity_ - read_pos_ % capacity_;
  memcpy(const_cast<char*>(peek_.data()), buffer_ + read_pos_ % capacity_, min(read_left, bytes_buffered()));
  if (bytes_buffered() > read_left) {
    memcpy(const_cast<char*>(peek_.data()+read_left), buffer_, bytes_buffered() - read_left);
  }
  return string_view{peek_.data(), bytes_buffered()};
}

bool Reader::is_finished() const
{
  return is_closed_ && bytes_buffered() == 0;
}

bool Reader::has_error() const
{
  return has_err_;
}

void Reader::pop( uint64_t len )
{
  if (len > write_pos_ - read_pos_) {
    len = write_pos_ - read_pos_;
  }
  read_pos_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  return (write_pos_ - read_pos_);
}

uint64_t Reader::bytes_popped() const
{
  return read_pos_;
}
