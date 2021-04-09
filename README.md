# ledmusic2.0
## REQUIREMENTS
Boost::system
```bash
sudo apt install libboost-system-dev
```
Protobuf
```bash
git clone https://github.com/google/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make -j4
sudo make install
sudo ldconfig
```
