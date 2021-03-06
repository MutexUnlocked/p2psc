#pragma once

#include <condition_variable>
#include <p2psc/mediator.h>
#include <p2psc/message/message.h>
#include <p2psc/message/types.h>
#include <socket/local_listening_socket.h>
#include <src/util/key_to_identifier_store.h>
#include <thread>
#include <vector>

namespace p2psc {
namespace integration {
namespace util {

class FakeMediator {
public:
  FakeMediator(const SocketCreator &socket_creator);
  FakeMediator(const SocketCreator &socket_creator,
               const p2psc::Mediator &mediator);
  ~FakeMediator() throw();

  void run();
  void stop();

  void quit_after(message::MessageType message_type);
  void await_shutdown();

  p2psc::Mediator get_mediator_description() const;
  std::vector<std::string> get_received_messages() const;
  std::vector<std::string> get_sent_messages() const;

private:
  std::unique_ptr<socket::LocalListeningSocket> _socket;
  p2psc::Mediator _mediator;
  KeyToIdentifierStore _key_to_identifier_store;
  bool _is_running;
  message::MessageType _quit_after;
  std::thread _worker_thread;
  std::vector<std::thread> _handler_pool;
  std::vector<std::string> _received_messages;
  std::vector<std::string> _sent_messages;
  std::condition_variable _disconnect_cv;
  std::condition_variable _shutdown_cv;
  std::mutex _mutex;
  std::unordered_set<socket::SocketAddress> _completed_disconnects;
  std::uint8_t _protocol_version;

  void _run();
  void _handle_connection(std::shared_ptr<Socket> session_socket);
  void _add_to_disconnects(const socket::SocketAddress &address);
  void _wait_for_disconnect(const socket::SocketAddress &address);
  template <class T>
  void _send_and_log(std::shared_ptr<Socket> socket, const Message<T> &message);
  template <class T>
  Message<T> _receive_and_log(std::shared_ptr<Socket> socket);
};
}
}
}