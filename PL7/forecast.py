import menu_module as menu


if __name__ == '__main__':
    menu.print_menu()
    
    unit = "c"
    while True:

        opt_args = input().split()
        command = opt_args[0]

        match command:
            case 'current' if len(opt_args) == 2:
                    menu.current(opt_args[1], unit)
            case 'forecast' if len(opt_args) == 3 and opt_args[2].isnumeric():
                    menu.forecast(opt_args[1], opt_args[2], unit)
            case 'setunit' if  len(opt_args) == 2:
                    unit = menu.setunit(opt_args[1], unit)
            case 'getunit' if len(opt_args) == 1:
                    menu.getunit(unit)
            case 'exit' if len(opt_args) == 1:
                    exit()
            case _:
                print('Invalid option. Please check command list and input format:')
                menu.print_menu()