
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


class Exchange
{
public:
    virtual ~Exchange(){}
    virtual void connect() const = 0;
    virtual vector<float> getMarketData(const string&) const = 0;
};

class BinanceExchange : public Exchange
{
public:
    virtual void connect() const override {
        cout << "Connection to Binance" << endl;
    }
    virtual vector<float> getMarketData(const string& coin) const override {
        return {10, 12, 18, 14};
    }
};

class CoinbaseExchange : public Exchange
{
public:
    virtual void connect() const override {
        cout << "Connection to Coinbase" << endl;
    }
    virtual vector<float> getMarketData(const string& coin) const override {
        return {10, 12, 18, 20};
    }
};

class TradingBot
{
public:
    virtual ~TradingBot() {}
    void setExchange(shared_ptr<Exchange> exchange) {
        m_exchange = exchange;
    }
    virtual bool shouldBuy(const vector<float>& prices) const = 0;
    virtual bool shouldSell(const vector<float>& prices) const = 0;
    void checkPrices(const string& coin) const {
        m_exchange->connect();
        vector<float> prices = m_exchange->getMarketData(coin);
        bool should_buy = shouldBuy(prices);
        bool should_sell = shouldSell(prices);
        if (should_buy) {
            cout << "You should buy " << coin << endl;
        } else if (should_sell) {
            cout << "You should sell " << coin << endl;
        } else {
            cout << "No action needed for " << coin << endl;
        }
    }
private:
    shared_ptr<Exchange> m_exchange;
};

class AverageTrader : public TradingBot
{
public:
    float average(const vector<float>& lst) const {
        float sum_of_elems = 0.f;
        for (const auto& el : lst) {
            sum_of_elems += el;
        }
        return sum_of_elems / lst.size();
    }
    virtual bool shouldBuy(const vector<float>& prices) const override {
        return prices.back() < average(prices);
    }
    virtual bool shouldSell(const vector<float>& prices) const override {
        return prices.back() > average(prices);
    }
};

class MinMaxTrader : public TradingBot
{
public:
    virtual bool shouldBuy(const vector<float>& prices) const override {
        return prices.back() == *min_element(prices.begin(), prices.end());
    }
    virtual bool shouldSell(const vector<float>& prices) const override {
        return prices.back() == *max_element(prices.begin(), prices.end());
    }
};

int main()
{
    AverageTrader application1;
    shared_ptr<Exchange> exchange = make_shared<BinanceExchange>();
    application1.setExchange(exchange);
    application1.checkPrices("BTC/USD");
    cout << endl;
    MinMaxTrader application2;
    exchange = make_shared<CoinbaseExchange>();
    application1.setExchange(exchange);
    application1.checkPrices("BTC/USD");
    cout << endl;
    application1.setExchange(make_shared<BinanceExchange>());
    application1.checkPrices("BTC/USD");
    cout << endl;

    shared_ptr<TradingBot> tbot = make_shared<AverageTrader>();
    tbot->setExchange(make_shared<BinanceExchange>());
    tbot->checkPrices("BTC/USD");
    cout << endl;
    tbot->setExchange(make_shared<CoinbaseExchange>());
    tbot->checkPrices("BTC/USD");
    cout << endl;
    tbot = make_shared<MinMaxTrader>();
    tbot->setExchange(make_shared<CoinbaseExchange>());
    tbot->checkPrices("BTC/USD");
    cout << endl;


    return 0;
}