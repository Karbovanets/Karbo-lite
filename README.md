This is the lite version of Karbo GUI. It works via remote daemon and doesn't store blockchain on your PC. The remote nodes are rewarded for their service. Karbo wallets, connected to masternode, are paying small additional fee (0.25% from the amount of transaction) to that node when are sending transactions through it. These fees are supposed to help to cover the costs of operating Karbo nodes.

You can select remote node in Settings or add custom one. Go to menu Settings -> Preferences -> Connection tab to select Remote daemon.

Portable on Windows - stores wallet files, logs, config file in the same folder with executable, stores data in the default folder on Linux and Mac (`~/.karbowanec` and `~/Library/Application Support/karbowanec` respectively).

Comes with config containing the list of remote nodes.

It can import wallet files from [classic Karbo wallet](https://github.com/seredat/karbowanecwallet) but it will take several minutes to refresh, and new wallet file will be incompatible with classic wallet.


**1. Clone wallet sources**

```
git clone https://github.com/Karbovanets/Karbo-lite.git
```

**2. Set symbolic link to coin sources at the same level as `src`. For example:**

```
ln -s ../karbowanec cryptonote
```

Alternative way is to create git submodule:

```
git submodule add https://github.com/seredat/karbowanec.git cryptonote
```

**3. Build**

```
mkdir build && cd build && cmake .. && make
```
