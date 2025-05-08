import tkinter as tk
import re

# Simulated JSON data (key: keyword, value: response)
faq_data = {
    "refund": "You can request a refund within 7 days of purchase.",
    "delivery": "Our standard delivery takes 3-5 business days.",
    "payment": "We support credit card, PayPal, and UPI payments.",
    "cancel": "You can cancel your order before it's shipped.",
    "support": "You can contact support at support@example.com."
}

# Function to find matching responses
def get_response(user_input):
    matches = []
    for key, value in faq_data.items():
        if re.search(rf"\b{key}\b", user_input, re.IGNORECASE):
            matches.append(value)
    return "\n".join(matches) if matches else "Sorry, I didn't understand that."

# GUI Logic
def respond():
    user_msg = entry.get()
    # entry.delete(0, tk.END)
    output = get_response(user_msg)
    # chatbox.config(state='normal')
    chatbox.insert(tk.END, f"You: {user_msg}\nBot: {output}\n\n")
    # chatbox.config(state='disabled')

# Minimal Tkinter UI
root = tk.Tk()
root.title("Customer Support Chatbot")
chatbox = tk.Text(root)
chatbox.pack(pady=10)
entry = tk.Entry(root, width=40)
entry.pack(side='left', padx=(10, 0), pady=(0, 10))
tk.Button(root, text="Send", command=respond).pack(side='right', padx=(0, 10), pady=(0, 10))

root.mainloop()
