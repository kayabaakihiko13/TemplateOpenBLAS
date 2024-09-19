# Compiler yang digunakan
CXX := g++
MYSYS_PATH := C:\msys64\mingw64

# Flags untuk kompilasi
CXXFLAGS := -O2 -Wall -I$(MYSYS_PATH)\include -ffast-math
LDFLAGS := -L$(MYSYS_PATH)\lib -lopenblas -fopenmp

# Nama target
TARGET := matrix_blas

# Sumber file
SOURCES := main.cc

# Aturan untuk membuat target executable
$(TARGET): $(SOURCES)
	$(CXX) -o $(TARGET) $(SOURCES) $(CXXFLAGS) $(LDFLAGS)

# Aturan untuk membersihkan file objek dan executable
clean:
	rm -f $(TARGET)

# Menggunakan phony targets untuk target yang tidak menghasilkan file
.PHONY: clean