#include <stdexcept>
#include <cstring>
#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
{
  allocator<char> alloc;
  buffer_ = alloc.allocate(capacity_);
}

ByteStream::~ByteStream() {

}

void Writer::push( string data )
{
  auto len = data.size();
  len = min(len, read_pos_ + capacity_ - write_pos_);
  auto first_len = min(len, capacity_ - write_pos_ % capacity_);
  memcpy(buffer_ + (write_pos_ % capacity_), data.data(), first_len);
  if (len > first_len) {
    memcpy(buffer_, data.data() + first_len, len - first_len);
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
  return capacity_;
}

uint64_t Writer::bytes_pushed() const
{
  return write_pos_;
}

string_view Reader::peek() const
{
  return string_view{&buffer_[read_pos_ % capacity_], 1};
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
  if (read_pos_ + len > write_pos_) {
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
