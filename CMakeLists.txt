cmake_minimum_required(VERSION 3.20)
project(hashing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# جلوگیری از استفاده از WinMain در سیستم‌عامل ویندوز
set(CMAKE_WIN32_EXECUTABLE OFF)

# مسیر فایل‌های هدر
include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/include)

# مسیر فایل‌های کتابخانه (در صورت وجود libbcrypt.a یا غیره)
link_directories(${PROJECT_SOURCE_DIR})

# ساخت دو برنامه اجرایی جداگانه
add_executable(main_exec main.cpp)

# اگر bcrypt استفاده می‌کنی، این خط رو برای هر دو اضافه کن:
#target_link_libraries(hashing bcrypt)
target_link_libraries(main_exec bcrypt)


