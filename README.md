# webserv

42seoul에서 진행하는 프로젝트로, C++을 활용하여 I/O Multiplexing 기반 Http Web Server를 구현합니다.
## 동작 
1. nginx.conf파일과 같은 형식으로 된 설정파일을 파싱합니다.
2. 파싱된 데이터를 기반으로 Socket을 생성하고 tcp 소켓, non-blocking으로 설정한 후 설정 포트에 bind하고 listen합니다.
3. Client Socket에서 connect할 때 accept함수가 return 하면서 클라이언트에게 대응 되는 Socket이 생성됩니다.
4. 2, 3의 과정에서 생성되는 소켓들을 실제로는 I/O Multiplexing System call인 kqueue를 활용하여 이벤트를 확인합니다. kqueue를 사용한 이유는 여러 Socket의 File Descriptor Event에 대해서 변경을 감지하기 위해서 이며 Select 방식보다 효율적이기 때문입니다. Select는 매번 Event 구조를 재생성 하지만 kqueue는 자체적인 큐를 보유하고 재사용합니다. https://stackoverflow.com/questions/17355593/why-is-epoll-faster-than-select 
5. Socket에서 Read event가 발생했다면 요청이 온 경우이고 Write event가 발생한다면 Response를 보내야하는 상황입니다.
6. Http 명세에 맞게 요청을 파싱하고 처리하여 적절한 응답코드와 함께 응답합니다.

## 실행
### 실행 명령어
make re && ./webserv config_files/default.conf

### 브라우저 다음 url 입력
localhost:8081/

### 성능 테스트
siege -b 127.0.0.1:8081

### 성능 테스트 트러블 슈팅
[소켓 close를 하지 않을 시 생기는 문제](https://velog.io/@xogml951/IO-Multiplexing-Custom-%EC%A0%95%EC%A0%81-%EC%84%9C%EB%B2%84-%EA%B5%AC%ED%98%84-%EC%84%B1%EB%8A%A5-%ED%85%8C%EC%8A%A4%ED%8A%B8Nginx)

## Team 
[sorikikikim](https://github.com/sorikikikim) / [Hyeon2Nam](https://github.com/Hyeon2Nam) / [xogml123](https://github.com/xogml123)

[Subject](https://cdn.intra.42.fr/pdf/pdf/13265/en.subject.pdf)

## 정리한 개념
1. [Blocking, Non-Blocking, Synchronous, Asynchronous의 개념 ](https://indigo-catsup-e60.notion.site/Webserv1-Blocking-Non-Blocking-Synchronous-Asynchronous-e6db7d39cc6b4e28a5d4b1377e948fc9)
2. [여러 웹서버 I/O의 구성 방식](https://indigo-catsup-e60.notion.site/Webserv2-I-o-fc139bed37a644e6b0f7b1eb66aa937f)
3. [select vs kqueue](https://indigo-catsup-e60.notion.site/Webserv3-select-vs-kqueue-e9dd38af16634f83836a5f87873d8a78)
4. [Nginx System](https://indigo-catsup-e60.notion.site/Webserv4-Nginx-System-bc551af2af2645caa11834714d6f557b)
5. [Blocking-Multi-thread vs Non-Blocking-Single-Thread](https://indigo-catsup-e60.notion.site/Webserv5-Blocking-Multi-thread-vs-Non-Blocking-Single-Thread-6e4abca116d14e9790401e4594e2632e)

## 참고자료


### Server setup

[How to build a simple HTTP server](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)

[Simple server with C++](https://ncona.com/2019/04/building-a-simple-server-with-cpp/)

[C++ Web Programming](https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm)

### HTTP 1.1 (standard to follow) :

[HTTP/1.1 (RFC 2616)](https://www.rfc-editor.org/rfc/rfc2616.html)

[HTTP/1.1 : Message Syntax and Routing (RFC 7230)](https://www.rfc-editor.org/rfc/rfc7230.html)

[HTTP/1.1 : Semantics and Content (RFC 7231)](https://www.rfc-editor.org/rfc/rfc7231.html)

[HTTP/1.1 : Conditional Requests (RFC 7232)](https://www.rfc-editor.org/rfc/rfc7232.html)

[HTTP/1.1 : Range Requests (RFC 7233)](https://www.rfc-editor.org/rfc/rfc7233.html)

[HTTP/1.1 : Caching (RFC 7234)](https://www.rfc-editor.org/rfc/rfc7234.html)

[HTTP/1.1 : Authentication (RFC 7235)](https://www.rfc-editor.org/rfc/rfc7235.html)

### Other HTTP (legacy / future) :

[HTTP/1.0 (RFC 1945)](https://www.rfc-editor.org/rfc/rfc1945.html)

[HTTP/2 (RFC 7240)](https://www.rfc-editor.org/rfc/rfc7540.html)

[HTTP/2 : Header Compression (RFC 7241)](https://www.rfc-editor.org/rfc/rfc7541.html)

[FTP (RFC 959)](https://www.rfc-editor.org/rfc/rfc959.html)

### HTTP Header Syntax

[HTTP Request Methods](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol#Request_methods)

[HTTP Status Codes](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)

[HTTP Header Break Style](https://stackoverflow.com/questions/5757290/http-header-line-break-style)

### Select and non-blocking

[Select](https://www.lowtek.com/sockets/select.html)

[Non-blocking I/O](https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_72/rzab6/xnonblock.htm)

### CGI

[CGI : Getting Started](http://www.mnuwer.dbasedeveloper.co.uk/dlearn/web/session01.htm)

[CGI 1.1 Documentation](http://www.wijata.com/cgi/cgispec.html#4.0)

