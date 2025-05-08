import tkinter as tk
import nltk
import re

info={
    "support":"can contact at 11001100 or email us at abc@gmail.com",
    "delivery":"in 2-3 days"
}

def get_response(user_input):
    response=[]
    for key,value in info.items():
        if re.search(rf"\b{key}\b",user_input,re.IGNORECASE):
            response.append(value)
    return "\n".join(response) if response else "Question is not related to our field."

def respond():
    user_input=entry.get()
    response=get_response(user_input)
    entry.delete(0,tk.END)
    chat.insert(tk.END,f"YOU : {user_input}\n BOT : {response}")

root=tk.Tk()
root.title("chatbot ui")

# chat
chat=tk.Text(root,width=40)
chat.pack(pady=10)

# entry
entry=tk.Entry(root,width=40)
entry.pack(side='left',pady=5,padx=5)

# root
send_btn=tk.Button(root,text='submit',command=respond)
send_btn.pack(side='left',pady=10,padx=10)

root.mainloop()