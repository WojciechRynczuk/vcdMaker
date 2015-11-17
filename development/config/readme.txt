Use this command to format souces before integrating them:
astyle --options=format.cfg $(find ./sources -name "*.[ch]*")

Use this command to create the CCCC documentation:
dir /b /s *.cpp *.c *.s | cccc -

Use Windows endings:
sed -i 's/\r//' $(find ./sources -name "*.*")
