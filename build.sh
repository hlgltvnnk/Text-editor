cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build

cp ./build/app/utext .
chmod 777 utext

