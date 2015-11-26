# bit by bit

```
     _/        _/        _/
    _/_/_/    _/_/_/    _/_/_/
   _/    _/  _/    _/  _/    _/
  _/    _/  _/    _/  _/    _/
 _/_/_/    _/_/_/    _/_/_/
 
```

## type utilities

### get type syntax sugar

```cpp
typename T::type t;
get_type<T> t; // same above
```

### type_traits syntax sugar

## container utilities

### revesed range

```cpp
for(auto &v : bbb::make_reverse(vec)) {
	std::cout << v << std::endl;
}
```

### simple for_each

```cpp
bbb::for_each(vec, [](){});
```

### byte array (maybe iterator will be implemented)

```cpp
byte_array<int> bytes = 8;
for(std::size_t i = 0; i < bbb::bytes.size(); i++) {
	std::cout << bytes[i] << std::endl;
}
```

### range

```cpp
for(auto v : bbb::range(100)) {
	std::cout << v << std::endl;
}
```

### enumerate (incomplete)

```cpp
for(auto v : bbb::enumerate(vec)) {
	std::cout << v.index() << ":" << v.value() << std::endl;
}
```

## thread utilities

* sleep
* simple multithread

## math utilities

* random

## reusable array
