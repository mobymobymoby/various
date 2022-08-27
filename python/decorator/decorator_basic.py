# deco: function -> function
def deco(function):
    def wrapper():
        print(">", function.__name__, "<")
    return wrapper

@deco
def main():
    print("[main]")
    print("ignored")

main()
