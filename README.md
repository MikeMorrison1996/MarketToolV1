Here’s a **GitHub description** for your project:

---

## MarketTool - Crypto Sentiment Analyzer

**MarketTool** is a C++ application designed to analyze market sentiment for cryptocurrencies and stocks using real-time data from social media and financial news. It leverages the power of the **OpenAI ChatGPT API** for natural language processing and analysis, combined with the **CURL** library for fetching data from sources like **Twitter** and **Reddit**.

### Key Features:
- **Real-time sentiment analysis**: Pulls data from platforms such as **Twitter** and **Reddit** to gauge market sentiment.
- **Graphical User Interface**: Built with **wxWidgets**, the app offers a clean and interactive dashboard for monitoring sentiment, viewing graphs, and making buy/sell decisions.
- **Integrated ChatGPT API**: Utilizes OpenAI's language model to process and analyze raw text, providing insights into market trends.
- **CURL-based data fetching**: Uses the **libcurl** library to fetch social media and news data in real-time.
  
### Technologies:
- **C++** (core logic and API integration)
- **wxWidgets** (for GUI)
- **CURL** (for HTTP requests)
- **nlohmann/json** (for JSON handling)
- **OpenAI ChatGPT API** (for natural language processing)

### How to Run:
1. Clone the repository.
2. Install dependencies:
   - **libcurl**
   - **wxWidgets**
   - **nlohmann/json**
3. Set your OpenAI API key as an environment variable:
   ```bash
   export OPENAI_API_KEY="your_api_key_here"
   ```
4. Build and run the project using **CMake**.

### Future Enhancements:
- **Historical data analysis**: Integrating historical data from financial markets for backtesting.
- **More platforms**: Adding support for additional social media platforms and financial news sources.
