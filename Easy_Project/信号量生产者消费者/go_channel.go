var messageBuffer = make(chan int, 3)   //  缓冲为3*int的大小的队列  管道
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


//http://legendtkl.com/2017/07/30/understanding-golang-channel/
