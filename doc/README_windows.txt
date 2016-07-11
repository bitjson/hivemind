Hivemind Core 0.10.99
=====================

Intro
-----
Hivemind is a free open source peer-to-peer electronic cash system that is
completely decentralized, without the need for a central server or trusted
parties.  Users hold the crypto keys to their own money and transact directly
with each other, with the help of a P2P network to check for double-spending.

Setup
-----
Unpack the files into a directory and run hivemind-qt.exe.

The default location of the Hivemind configuration file is 
C:\Users\<username>\AppData\Roaming\Hivemind\hivemind.conf. It should contain 
at least two entries, rpcuser and rpcpassword. Hivemind testnet users should 
run Hivemind with `-testnet=1` or add `testnet=1` to their configuration file.

Hivemind Core is the original Hivemind client and it builds the backbone of the network.
However, it downloads and stores the entire history of Hivemind transactions;
depending on the speed of your computer and network connection, the synchronization
process can take anywhere from a few hours to a day or more.

See the hivemind wiki at:
  https://en.hivemind.it/wiki/Main_Page
for more help and information.
