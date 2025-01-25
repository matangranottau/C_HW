import subprocess
import difflib

executable_path = "C:\\Users\\matan\\source\\repos\\C_HW\\HW5\\x64\\test\\HW5.exe"
base_files_path = "C:\\Users\\matan\\source\\repos\\C_HW\\HW5\\hw5_examples_2025_01_19"
inputs_path = f"{base_files_path}\\inputs"
outputs_path = f"{base_files_path}\\outputs"
expecteds_path = f"{base_files_path}\\expected"
tests = [
    {
        'input_name': 'dec_example1_in_0.txt', 'output_name': 'dec_example1_out_0.txt', 'operation': 'dec',
        'enc_type': '0', 'blacklist_path': ''
    },
    {'input_name': 'dec_example1_in_1.txt', 'output_name': 'dec_example1_out_1.txt', 'operation': 'dec',
     'enc_type': '1', 'blacklist_path': ''},
    {'input_name': 'dec_example1_in_2.txt', 'output_name': 'dec_example1_out_2.txt', 'operation': 'dec',
     'enc_type': '2', 'blacklist_path': ''},
    {'input_name': 'dec_example1_in_3.txt', 'output_name': 'dec_example1_out_3.txt', 'operation': 'dec',
     'enc_type': '3', 'blacklist_path': ''},
{
        'input_name': 'example1_in.txt', 'output_name': 'enc_example1_out_0.txt', 'operation': 'enc', 'enc_type': '0', 'blacklist_path': ''
    },
    {'input_name': 'example1_in.txt', 'output_name': 'enc_example1_out_1.txt','operation': 'enc', 'enc_type': '1', 'blacklist_path': ''},
    {'input_name': 'example1_in.txt', 'output_name': 'enc_example1_out_2.txt', 'operation': 'enc', 'enc_type': '2', 'blacklist_path': ''},
    {'input_name': 'example1_in.txt', 'output_name': 'enc_example1_out_3.txt', 'operation': 'enc', 'enc_type': '3', 'blacklist_path': ''},
    {'input_name': 'example1_in.txt', 'output_name': 'censor_example1_out.txt', 'operation': 'censor', 'enc_type': '0', 'blacklist_path': 'example1_blacklist'}

]
def compare_files(output_file, expected_file):
    try:
        with open(output_file, 'rb') as of, open(expected_file, 'rb') as ef:
            output_data = list(of.read())
            expected_data = list(ef.read())
            if output_data != expected_data:
                print("output data:")
                print(output_data)
                print("expected data:")
                print(expected_data)
                for i in range(len(output_data)):
                    if output_data[i] != expected_data[i]:
                        print(f"location {i}, output[{i}]={output_data[i]}, expected[{i}]={expected_data[i]}")
                        return False
            return output_data == expected_data
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return False
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        return False

def run_test(test_params: dict):
    test_name = test_params['input_name']
    test_output_name = test_params['output_name']
    input_name: str = f"{inputs_path}\\{test_name}"
    output_name: str = f"{outputs_path}\\{test_output_name}"
    expected_name: str = f"{expecteds_path}\\{test_output_name}"
    operation: str = test_params['operation']
    enc_type: str = test_params['enc_type']
    blacklist_path: str = test_params['blacklist_path']
    command = f"{executable_path} -p {operation} -t {enc_type} -i {input_name} -o {output_name}"
    if blacklist_path:
        command += f" -b {inputs_path}\\{blacklist_path}"
    print(f"running {command}")
    res = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(res.stdout)
    if compare_files(output_name, expected_name):
        print(f"test {test_name} passed")
    else:
        print(f"test {test_name} failed")



def run_all_tests():
    for test in tests:
        run_test(test)

def main():
    run_all_tests()

if __name__ == '__main__':
    main()