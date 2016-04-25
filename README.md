Hivemind Core integration/staging tree
=====================================

[http://www.bitcoin-hivemind.com](http://www.bitcoin-hivemind.com)

What is Hivemind?
----------------

Hivemind is an ambitious modification of Bitcoin, which extends Bitcoin's abilities (to send and receive value-tokens) by adding the ability to create and participate in [markets for event derivatives ("prediction markets")](https://en.wikipedia.org/wiki/Prediction_market).

Although substantially more complex, Hivemind offers correspondingly substantial benefits, having potentially world-changing implications for science, taxation, corporate governance and politics.

Hivemind includes two types of value-token.  One, "Bitcoin", is used for storing value, buying/selling in markets and paying transaction fees to miners. This coin will resemble Bitcoin-testnet-money (an "Altcoin") for the duration of pre-release testing, and will then be a [sidechain](http://www.blockstream.com/) of Bitcoin. Therefore, the network will "accept" Bitcoin (indeed, this will be the only currency the network accepts). The second (less important) token, "VoteCoin", is used to track a smaller group of special users and reward them for providing reports to the blockchain on the status of the bet-upon events.

For an immediately useable, binary version of the Hivemind Core software, see [Hivemind Builds](http://107.170.174.203/Builds/).

For more information, including the original whitepaper, please see the [Hivemind website](http://bitcoinhivemind.com/).

License
-------

Hivemind Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.


Current Install Instructions
---------------------------
To build on Linux, follow the fullnode setup guide (see [doc/fullnode-setup.txt](doc/fullnode-setup.txt))

To compile releases on Debian 64-bit Precise for Linux, Windows and Mac, see 
the Gitian build instructions (see [doc/gitian-building.md](doc/gitian-building.md))
and (see [doc/release-process.md](doc/release-process.md)) 


Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Hivemind
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then discussion
should take place on relevant pull requests and issues on the Bitcoin Hivemind github page.
Changes will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/developer-notes.md](doc/developer-notes.md)) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/hivemind/hivemind/tags) are created
regularly to indicate new official, stable release versions of Hivemind.


Testing / Where to start
-------

### The Hivemind project maintains a repository with everything a developer needs to start testing and working on the Bitcoin Hivemind project, as well as a network with nodes containing canonical blockchain data to work with.
https://github.com/bitcoin-hivemind/testnet-canonical

### To find something to work on, see the issues page or the Hivemind roadmap:
http://bitcoinhivemind.com/blog/roadmap/
