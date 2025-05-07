import streamlit as st
from nltk.chat.util import Chat, reflections

# Define chatbot pairs
pairs = [
    # Greetings
    [r"(?i).*\b(hi|hello|hey|good (morning|afternoon|evening))\b.*", 
    ["Hello! How can I assist you today?", "Hi there! How may I help you?"]],
    
    [r"(?i).*\b(what('| i)?s|what is)\b.*\byour name\??\b.*", 
    ["I'm ShopBot, your virtual assistant."]],
    
    [r"(?i).*\b(what can you do|how can you help( me)?|how do you work)\b.*", 
    ["I can help you with orders, returns, refunds, product info, discounts, and more."]],

    # Order Tracking
    [r"(?i).*\b(where is|track|status of)\b.*\b(my|the)? ?order\b.*", 
    ["Please provide your order ID to track it."]],
    
    [r"(?i).*\b(ord(er)?)[\s\-:]?(\d+)\b.*", 
    ["Fetching details for your order. Please wait..."]],

    # Returns & Exchanges
    [r"(?i).*\b(how do i return|return item|i want to return|i need to return)\b.*", 
    ["Please provide your order ID to initiate the return process."]],
    
    [r"(?i).*\b(exchange (an )?item|how do i exchange|i want to exchange)\b.*", 
    ["You can exchange items within 30 days of delivery. Would you like the exchange link?"]],

    # Cancel Orders
    [r"(?i).*\b(cancel order|how do i cancel|i want to cancel)\b.*", 
    ["Please provide the order ID you'd like to cancel."]],

    # Refund
    [r"(?i).*\b(refund status|where is my refund|i want a refund)\b.*", 
    ["Please provide your order ID to check the refund status."]],

    # Payment Issues
    [r"(?i).*\b(payment (failed|issue|problem)|can't pay|error while paying|payment not working)\b.*", 
    ["Sorry for the inconvenience. Please try a different payment method or contact support."]],

    # Promotions & Discounts
    [r"(?i).*\b(promotion|discounts?|sales?|offers?)\b.*", 
    ["We have a special 10 percent discount for first-time customers. Want to know more?"]],
    
    [r"(?i).*\b(apply|use)\b.*\b(discount|coupon|promo code)\b.*", 
    ["You can apply the coupon code at checkout. Do you have one?"]],

    # Account Management
    [r"(?i).*\b(create|open|register|sign up for)\b.*\b(account|profile)\b.*", 
    ["You can create an account by providing your email and password. Would you like to proceed?"]],
    
    [r"(?i).*\b(login|log in|sign in)\b.*", 
    ["Please enter your email and password to login."]],
    
    [r"(?i).*\b(forgot|reset)\b.*\bpassword\b.*", 
    ["Click on the 'Forgot Password' link on the login page to reset it."]],

    # Product Inquiry
    [r"(?i).*\b(tell me about|what is|describe)\b.*\b(product|item)\b.*", 
    ["Could you please specify the product you're interested in?"]],
    
    [r"(?i).*\b(where can i buy|how to buy|buy)\b.*", 
    ["You can buy it directly on our website or visit a nearby store."]],

    # Shipping Information
    [r"(?i).*\b(shipping|delivery|how long does it take|when will it arrive)\b.*", 
    ["Shipping typically takes 5-7 business days. Would you like to know about the shipping options?"]],
    
    [r"(?i).*\b(change|update)\b.*\b(shipping address|address)\b.*", 
    ["Please provide your order ID and new address details."]],

    # Customer Support
    [r"(?i).*\b(support hours|when are you available|customer service hours)\b.*", 
    ["Our support is available 24/7 through chat and email."]],
    
    [r"(?i).*\b(how can i contact support|contact support|reach customer service)\b.*", 
    ["You can reach us by email at support@example.com or via live chat here."]],

    # Technical Support
    [r"(?i).*\b(product not working|can't use|issue with product|device problem)\b.*", 
    ["I'm sorry you're facing an issue. Could you describe the problem you're having?"]],
    
    [r"(?i).*\b(technical support|troubleshooting|fix issue|problem fix)\b.*", 
    ["Let's troubleshoot together! Please tell me the issue you're experiencing."]],

    # FAQs
    [r"(?i).*\b(what is your return policy|how to return items|return policy)\b.*", 
    ["Items can be returned within 30 days of delivery. Would you like to initiate a return?"]],
    
    [r"(?i).*\b(how do i track my order|track order)\b.*", 
    ["Please provide your order ID, and I will track it for you."]],

    # Feedback & Suggestions
    [r"(?i).*\b(give feedback|suggestion|complaint|i have feedback)\b.*", 
    ["We'd love to hear your feedback! Please tell me your thoughts."]],

    # Gratitude
    [r"(?i).*\b(thank you|thanks|thx)\b.*", 
    ["You're welcome! Anything else I can assist you with?"]],

    # Goodbye
    [r"(?i).*\b(bye|goodbye|exit|see you)\b.*", 
    ["Goodbye! Feel free to return anytime."]],

    # Fallback
    [r".*", 
    ["Sorry, I didn't understand that. Could you try rephrasing your question?"]]
]

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