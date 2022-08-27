def deco_with_args(addr, value):
    def deco(function):
        def wrapper(arg):
            print(f"BEGIN: {function.__name__}({arg})")
            if (addr == 0x1000):
                print("special operation", value)
            function(arg)
            print(f"  END: {function.__name__}({arg})\n")

        return wrapper

    return deco

@deco_with_args(0x1000, 20)
def main(state):
    print("[main]", state)

@deco_with_args(0x1001, 200)
def foo(state):
    print("[foo]", state)

main("XXX")
foo("YYY")
