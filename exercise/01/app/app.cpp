﻿#include <iostream>
#include <utility>

#include <windows.h>
#include <tchar.h>

#include "../dll2/public.h"
#include "../lib/public.h"

using get_value_decl = double(int);

std::pair<HMODULE, get_value_decl*> load_library()
{
  auto library_handle = LoadLibrary(_T("dynamic_library.dll"));
  if (library_handle == nullptr)
    std::terminate();

  auto proc_handle = reinterpret_cast<get_value_decl*>(GetProcAddress(library_handle, "get_value"));
  if (proc_handle == nullptr) 
  {
    FreeLibrary(library_handle);
    std::terminate();
  }

  return std::make_pair(library_handle, proc_handle);
}

int main()
{
  auto[library_handle, proc_handle] = load_library();
  std::cout << "static library: " << static_lib::get_value(2) << '\n';
  std::cout << "dll: " << proc_handle(2) << '\n';
  std::cout << "dll with import lib: " << get_value(2) << '\n';
  FreeLibrary(library_handle);
}
