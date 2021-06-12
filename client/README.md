# Các hàm trong client
## Request
### Login/Signup/Logout
- Khởi tạo User mặc định
-  Mỗi client chỉ được phép dùng 1 user
- Chức năng login thì gọi hàm login_request từ user vừa tạo
- Chức năng signup thì gọi hàm signup_request từ user vừa tạo
- Chức năng logout thì gọi hàm logout_request từ user vừa tạo

### Create/Get/Join/Quit Lobby and Startgame
- Khởi tạo một Lobby mặc định
- Lobby sẽ lưu thông tin về phòng của người chơi
- Chức năng create_lobby gọi hàm create_lobby từ lobby vừa tạo
- Chức năng get_lobby gọi hàm get_lobby (hàm này gọi ngay sau khi đăng nhập thành công hoặc sau khi người chơi thoát phòng cùng với nút refresh phòng chơi)từ lobby vừa tạo để lấy danh sách phòng chơi hiển thị tất cả các phòng
- Chức năng join_lobby sẽ tham gia vào phòng với id và lưu tất cả thông tin về phòng vào lobby vừa tạo
- Chức năng quit_lobby sẽ thoát ra ngoài phòng chờ, các thông tin về lobby cũ vẫn giữ nguyên trong biến lobby và thông tin player cũ cũng vậy(nên chuyển UI sang phòng chờ)
- Chức năng start_game sẽ khởi tạo biến Game với tham số truyền vào là thông tin của lobby vừa nãy

### Ready/Unread/Change team
- Khi có được thông tin người chơi sau khi tạo phòng hoặc vào phòng chơi ta lưu vào trong biến Player
- Chức năng ready để yêu cầu sẵn sàng
- Chức năng unready để yêu cầu hủy sẵn sàng
- Chức năng change team để chuyển đội chơi

## Response
- receive_data: Đây là hàm gọi trong thread để bắt tất cả các response từ server

### Login/Signup/Logout
- Được gọi từ biến user
- login_response: Nhận phản hồi từ server, nếu thành công thì trạng thái của user chuyển từ USER_NONAUTH sang USER_AUTH( cần check trang thái chuyển vào phòng chơi)
Ngoài ra còn các thông báo khác từ server
- signup_response: Nhận phản hồi đăng kí từ server, nếu đăng ký thành công thì chuyển sang đăng nhập, tên username được lưu lại trong user để không phải nhập lại
Ngoài ra còn các thông báo khác từ server
- logout_response: Nhận phản hồi từ server đã thoát thành công và chuyển về trang login

### Create/Get/Join/Quit Lobby and Startgame
- Được gọi từ biến lobby
- create_lobby_response: Nhận phản hồi và tạo thông tin về phòng của người chơi(sau khi thành công sẽ chuyển UI sang phòng chơi) lúc này sẽ khởi tạo một biến Player để lưu thông tin của người chơi(team nào, id bao nhiêu mặc định người tạo là id=0 team=0)
- get_lobby_response: Nhận phản hồi và trả về danh sách các phòng(nhớ tạo 1 mảng để lưu thông tin phòng)
- join_lobby_response: Nhận phản hồi và hàm đã nhận thông tin của người chơi trả về biến Player(sau đó server sẽ trả về 1 response chứa toàn bộ danh sách các người chơi, khi đó cần phải hiện thị thông tin lobby )
- quit_lobby_response: Nhận phản hồi và chuyển về phòng chờ
- start_game_response: Nhận phản hồi thành công thì khởi tạo biến Game từ lobby này

### Ready/Unready/Change team
- Được gọi từ biến player
- ready_response: Nhận phản hồi và người chơi chuyển sang trạng thái sẵn sàng
- unread_response: Nhận phản hồi và người chơi chuyển sang trạng thái không sẵn sàng
- change_team_response: Nhận phản hồi và thông tin về đội của người chơi thay đổi

### Response chỉ từ server(tự động cập nhật)
- Update lobby: chỉ xảy ra khi có sự thay đổi trong phòng chơi như có người vào người ra, người chơi sẵn sàng hoặc bỏ sẵn sàng, chuyển đội (join, quit lobby, ready, unready, change_team)
- 






