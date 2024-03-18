FROM alpine as build

RUN apk add cmake make g++ hidapi-dev
RUN mkdir /temper
WORKDIR /temper
COPY . ./
RUN cmake . && make


FROM alpine

RUN apk add hidapi curl bash
RUN mkdir -p /temper/utils
COPY --from=build /temper/libtempered/*.so* /temper/libtempered/
COPY --from=build /temper/libtempered-util/*.so* /temper/libtempered-util/
COPY --from=build /temper/utils/tempered /temper/utils/
COPY entrypoint.sh /temper
WORKDIR /temper/utils

ENTRYPOINT ../entrypoint.sh
