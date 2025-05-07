import streamlit as st
from nltk.chat.util import Chat, reflections

# Define chatbot pairs
pairs = [
    # Greetings
    [r"(hi|hello|hey|good morning|good afternoon|good evening)", ["Hello! How can I assist you today?", "Hi there! How may I help you?"]],
    [r"(what's|what is) your name\??", ["I'm ShopBot, your virtual assistant."]],
    [r"(what can you do|how can you help me|how do you work)", ["I can help you with orders, returns, refunds, product info, discounts, and more."]],
    
    # Order Tracking
    [r"(where is|track|status of) (my )?order", ["Please provide your order ID to track it."]],
    [r"(ord|order)[\s\-:]?(\d+)", ["Fetching details for your order. Please wait..."]],
    
    # Returns & Exchanges
    [r"(how do i return|return item|i want to return)", ["Please provide your order ID to initiate the return process."]],
    [r"(exchange item|how do i exchange)", ["You can exchange items within 30 days of delivery. Would you like the exchange link?"]],
    
    # Cancel Orders
    [r"(cancel order|how do i cancel|i want to cancel)", ["Please provide the order ID you'd like to cancel."]],
    
    # Refund
    [r"(refund status|where is my refund|i want a refund)", ["Please provide your order ID to check the refund status."]],
    
    # Payment Issues
    [r"(payment (failed|issue|problem)|can't pay|error while paying)", ["Sorry for the inconvenience. Please try a different payment method or contact support."]],
    
    # Promotions & Discounts
    [r"(promotion|discount|sale|offers)", ["We have a special 10% discount for first-time customers. Want to know more?"]],
    [r"(apply|use) (discount|coupon)", ["You can apply the coupon code at checkout. Do you have one?"]],
    
    # Account Management
    [r"(create account|register|sign up)", ["You can create an account by providing your email and password. Would you like to proceed?"]],
    [r"(login|sign in)", ["Please enter your email and password to login."]],
    [r"(forgot password|reset password)", ["Click on the 'Forgot Password' link on the login page to reset it."]],
    
    # Product Inquiry
    [r"(tell me about|what is|describe) (product|item) (.*)", ["Could you please specify the product you're interested in?"]],
    [r"(where can i buy|how to buy|buy (.*))", ["You can buy it directly on our website or visit a nearby store."]],
    
    # Shipping Information
    [r"(shipping|delivery|how long does it take)", ["Shipping typically takes 5-7 business days. Would you like to know about the shipping options?"]],
    [r"(change shipping address|update address)", ["Please provide your order ID and new address details."]],
    
    # Customer Support
    [r"(support hours|when are you available|customer service hours)", ["Our support is available 24/7 through chat and email."]],
    [r"(how can i contact support|contact support)", ["You can reach us by email at support@example.com or via live chat here."]],
    
    # Technical Support
    [r"(product not working|can't use|issue with product)", ["I'm sorry you're facing an issue. Could you describe the problem you're having?"]],
    [r"(technical support|troubleshooting|fix issue)", ["Let's troubleshoot together! Please tell me the issue you're experiencing."]],
    
    # FAQs
    [r"(what is your return policy|how to return items)", ["Items can be returned within 30 days of delivery. Would you like to initiate a return?"]],
    [r"(how do i track my order|track order)", ["Please provide your order ID, and I will track it for you."]],
    
    # Feedback & Suggestions
    [r"(give feedback|suggestion|complaint)", ["We'd love to hear your feedback! Please tell me your thoughts."]],
    
    # Gratitude
    [r"(thank you|thanks|thx)", ["You're welcome! Anything else I can assist you with?"]],
    
    # Goodbye
    [r"(bye|goodbye|exit|see you)", ["Goodbye! Feel free to return anytime."]],
    
    # Fallback
    [r"(.*)", ["Sorry, I didn't understand that. Could you try rephrasing your question?"]]
]


# Initialize chatbot
def get_chatbot():
    return Chat(pairs, reflections)

# Streamlit setup
st.set_page_config(page_title="ShopBot - Customer Service")
st.title("ShopBot - Your Customer Support Assistant")

# Session state setup
if "bot" not in st.session_state:
    st.session_state.bot = get_chatbot()

if "history" not in st.session_state:
    st.session_state.history = []

# Display conversation
for role, msg in st.session_state.history:
    with st.chat_message(role):
        st.markdown(msg)

# Input box at the bottom (without using :=)
prompt = st.chat_input("Type your message")
if prompt:
    # Save and display user message
    st.session_state.history.append(("user", prompt))
    with st.chat_message("user"):
        st.markdown(prompt)

    # Get bot response and display it
    response = st.session_state.bot.respond(prompt)
    st.session_state.history.append(("assistant", response))
    with st.chat_message("assistant"):
        st.markdown(response)
