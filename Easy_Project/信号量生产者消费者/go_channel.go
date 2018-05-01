var messageBuffer = make(chan int, 3)
func produce () {
 for i := 0; i < 1000; i++ {
 messageBuffer <- i
 }
}
func consume () {
 for {
 message := <- messageBuffer
 fmt.Println(message)
 }
}
func main () {
 go produce()
 go consume()
}
