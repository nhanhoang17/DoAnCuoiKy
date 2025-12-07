🎮 Tetris Mini Project
I. Giới thiệu

Dự án Tetris Mini Project là một trò chơi xếp gạch kinh điển được nhóm chúng tôi xây dựng nhằm luyện tập tư duy lập trình, quản lý dự án và kỹ năng làm việc nhóm trong môi trường phát triển phần mềm thực tế.

Trò chơi bao gồm các khối gạch với nhiều hình dạng khác nhau (I, L, J, O, S, Z, T) rơi từ trên xuống. Người chơi phải xoay và di chuyển các khối để lấp đầy hàng và ghi điểm.

Thành viên nhóm:

+Hoàng Hữu Vũ Nhân:Duyệt code và merge vào git.
+Phạm Minh Nguyên: viết lại giao diện chỗ viền và block sao cho vuông vức.
+Đặng Huyền Trân: viết hàm removeLine
+Mai Lương Khánh Vy: viết code mỗi lần removeL:ine thì tốc độ rơi nhanh hơn
+Phạm Chí Quang:nghiên cứu viết code chõ xoay block

II. Mục tiêu của dự án

Hiểu và cài đặt cấu trúc dữ liệu cho khối gạch.

Xử lý logic game loop (di chuyển, xoay, rơi tự động).

Rèn luyện kỹ năng làm việc nhóm, chia task, merge code, resolve conflict.

Làm quen với Git, GitHub workflow và review code.

II. Cách chơi

← →: Di chuyển khối sang trái/phải

↓: Tăng tốc độ rơi

↑: Xoay khối


Mỗi khi một hàng được lấp đầy, người chơi sẽ ghi điểm và hàng đó biến mất.

III. Công nghệ sử dụng

Ngôn ngữ:C++

IDE/Tool: Visual Studio, VS Code

Thư viện:

<conio.h> – xử lý input

<windows.h> – xử lý delay & giao diện console

Hoặc library đặc thù tùy hệ thống
